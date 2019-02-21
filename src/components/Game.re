module A = Relude.Array;
module S = Relude.String;
module StrMap = Belt.Map.String;

module LetterConstant = {
  let component = ReasonReact.statelessComponent(__MODULE__);
  let make = (~value, _) => {
    ...component,
    render: _ =>
      <div className="letter-constant"> {ReasonReact.string(value)} </div>,
  };
};

module Letter = {
  let valueFromEvent = evt => ReactEvent.Form.target(evt)##value;
  let component = ReasonReact.statelessComponent(__MODULE__);
  let make = (~value, ~guess=?, ~onGuess, _) => {
    ...component,
    render: _ =>
      <label className="letter-guess">
        <input value=?guess onChange={e => onGuess(valueFromEvent(e))} />
        <span> {ReasonReact.string(value)} </span>
      </label>,
  };
};

type state = {guesses: StrMap.t(string)};
type action =
  | SetGuess(string, string);

/* compare two string maps, ensuring that each (k, v) pair in the first is
   flipped as a (v, k) in the second. */
let validate = (dict, guesses) => /* TODO */ false;

let component = ReasonReact.reducerComponent(__MODULE__);
let make = (~quote, ~dict, _children) => {
  ...component,

  initialState: () => {guesses: StrMap.empty},

  reducer: (action, state) =>
    switch (action) {
    | SetGuess(scrambled, value) =>
      Update({guesses: StrMap.set(state.guesses, scrambled, value)})
    },

  render: ({state, send}) => {
    let {text, author}: Quote.t = quote;

    let renderLetter = letter =>
      switch (StrMap.get(dict, letter)) {
      | None => <LetterConstant value=letter />
      | Some(value) =>
        let guess = StrMap.get(state.guesses, value);
        let onGuess = v => send(SetGuess(value, v));
        <Letter value ?guess onGuess />
      };

    let renderWord = word => {
      <div className="word">
        ...{S.splitArray("", word) |> A.map(renderLetter)}
      </div>;
    };

    <p className="quote">
      ...{S.splitArray(" ", text) |> A.map(renderWord)}
    </p>;
  },
};
