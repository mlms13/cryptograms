let quotes = [
  Quote.make(
    "Go confidently in the direction of your dreams. Live the life you've imagined. As you simplify your life, the laws of the universe will be simpler.",
    Some("Henry David Thoreau"),
  ),
];

let getQuote = () =>
  switch (Relude.List.(shuffle(quotes) |> head)) {
  | Some(quote) => Future.value(Belt.Result.Ok(quote))
  | None => Future.value(Belt.Result.Error("No quote found"))
  };
