// fetch module
open Belt;
type res = string;

// make decoder
module Decode = {
	let ress = json: array(res) =>
		Json.Decode.(
			json |> field("message", array(string)) |> Array.map(_, res => res)
		);
};




let url = "http://felipearce.pw:3000/";
let fetchReponse = () =>
	Js.Promise.(
		Fetch.fetch(url)
		|> then_(Fetch.Response.text)
		|> then_(text => Js.log(text) |> resolve)
	);




module QueryForm = {
	open Formality;

	// naming fields in form
	type field = Query;

	// setting state for value retrieval later
	type state = {
		query: string
	};

	// type of message that form can return
	type message = string;

	// list types of submission errors (planned and unplanned)
	type submissionError = UnexpectedServerError;

	// field validators
	module QueryField = {
		// set update calls for later
		let update = (state, value) => {...state, query: value};
		// validators use strategy to set and check fields + states
		let validator = {
			field: Query,
			strategy: Strategy.OnFirstSuccessOrFirstBlur,
			dependents: None,
			validate: state =>
				switch (state.query) {
					// pattern match for empty input
					| "" => Error("Invalid Query")
					| _ => Ok(Valid)
					},
		};
	};

	let validators = [QueryField.validator,];
};

// hook for the query form
module QueryFormHook = Formality.Make(QueryForm);

[@react.component]
let make = () => {
	let form =
		QueryFormHook.useForm(
			~initialState={query: ""},
			~onSubmit=(state, form) => {
				Js.Promise.(
				Fetch.fetch("http://felipearce.pw:3000/")
				|> then_(Fetch.Response.text)
				|> then_(text => Js.log(text) |> resolve)
				);
				Js.log("inputted this" ++ state.query)
			},
		);
	// now form the actual jsx form
	<form onSubmit={form.submit->Formality.Dom.preventDefault}>
		<input
		value={form.state.query}
		disabled={form.submitting}
		onBlur={_ => form.blur(Query)}
		onChange={event =>
			form.change(
				Query,
				QueryForm.QueryField.update(
					form.state,
					event->ReactEvent.Form.target##value,
				),
			)
		}
		/>
		{switch (Query->(form.result)) {
			| Some(Error(message)) =>
			<div className="failure"> message->React.string </div>
			| Some(Ok(Valid | NoValue))
			| None => React.null
			}}
		<div style={ReactDOMRe.Style.make(
				~height="10px",
				()
		)}/>
		<button
		style={ReactDOMRe.Style.make(
				~height="50px",
				~width="80px",
				~color="blue",
				(),
		)}
		disabled={form.submitting}>
			(form.submitting ? "Submitting..." : "Submit") -> React.string
		</button>
	</form>;
};
