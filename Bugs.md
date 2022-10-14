# Bugs

## This is a file that records the bugs in the history

### Bug 0x0001

`Markdown Render : Adding <p> is my hobby`

```javascript
function rendMarkdown(str) {
  let res = "<p>";
  let status = {};
  for (let id = 0; str[id]; id++) {
    if (str[id] === '*' && str[id + 1] === '*' && !status.isCodeBlock && !status.isInLineBlock) {
      if (status.isBold) {
        status.isBold = 0;
        res += "</strong>";
      } else {
        status.isBold = 1;
        res += "<strong>";
      }
      id++;
    } else if (str[id] === '*' && !status.isCodeBlock && !status.isInLineBlock) {
      // ilatic
    } else if (str[id] === '`' && str[id + 1] === '`' && str[id + 2] === '`') {
      // codeblock
    } else if (str[id] === '`' && !status.isCodeBlock) {
      // inline block
    } else if (str[id] === '~' && str[id + 1] === '~' && !status.isCodeBlock && !status.isInLineBlock) {
      // deleted
    } else if (str[id] === '\n' && str[id + 1] === '\n' && !status.isCodeBlock && !status.isInLineBlock) {
      res += '</p><p>'; // start a <p>
      id++;// ~~^~~^~
    } else if (str[id] === '#' && !status.isCodeBlock && !status.isInLineBlock) {
      // ...
      res += "</p><h" + Math.min(cnt, 6) + ">" + s + "</h" + Math.min(cnt, 6) + "><p>";
      //      ~~^~                                                                ~^~
    } else if (str[id] === '[' && !status.isCodeBlock && !status.isInLineBlock) {
      // ...
    } else {
      if (str[id] === '<') {
        res += '&lt;';
      } else if (str[id] === '>') {
        res += "&gt;";
      } else {
        res += str[id];
      }
    }
  }
  res += "</p>";
  return res;
}
```

We solved it with `marked.js`， which requires nothing but only a function to use markdown:

```javascript
function rendMarkdown(str) {
  return marked.marked(str);
}
```

Of course, this doesn't solves any problems at all.