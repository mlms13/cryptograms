let component = ReasonReact.statelessComponent(__MODULE__);

let make = _children => {
  ...component,
  render: _self => <div> {ReasonReact.string("Hello, world!")} </div>,
};
