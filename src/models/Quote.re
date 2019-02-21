type t = {
  text: string,
  author: option(string),
};

let make = (text, author) => {text, author};
