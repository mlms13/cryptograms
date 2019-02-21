module R = Relude.Result;
module StrMap = Belt.Map.String;

type state =
  | Initial
  | Loading
  | InGame(Quote.t, StrMap.t(string))
  | Failure;

type action =
  | BeginGame
  | LoadQuote(Quote.t)
  | Fail;

let component = ReasonReact.reducerComponent(__MODULE__);
let make = _children => {
  ...component,
  initialState: () => Initial,
  reducer: (action, _) =>
    switch (action) {
    | BeginGame =>
      UpdateWithSideEffects(
        Loading,
        ({send}) =>
          Api.getQuote()
          ->Future.map(R.fold(q => LoadQuote(q), _ => Fail))
          ->Future.tap(send)
          ->ignore,
      )
    | LoadQuote(quote) => Update(InGame(quote, Alphabet.randomize()))
    | Fail => Update(Failure)
    },
  didMount: ({send}) => send(BeginGame),
  render: ({state}) =>
    <div>
      {switch (state) {
       | Initial => ReasonReact.string("Initial") /* TODO */
       | Loading => ReasonReact.string("Loading") /* TODO */
       | Failure => ReasonReact.string("Failure") /* TODO */
       | InGame(quote, dict) => <Game quote dict />
       }}
    </div>,
};
