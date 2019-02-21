let alpha = "abcdefghijklmnopqrstuvwxyz";

let randomize = () => {
  open Relude.List;
  let chars = Relude.String.splitList("", alpha);
  shuffle(chars) |> zip(chars) |> toArray |> Belt.Map.String.fromArray;
};
