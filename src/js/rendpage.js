var defaultDesc = {
  writable: true,
  enumerable: true,
  configurable: true
};
var katexConfig = {
  delimiters: [
    {left: "$$", right: "$$", display: true},
    {left: "$", right: "$", displsy: false},
    {left: "\\[", right: "\\]", display: true},
    {left: "\\(", right: "\\)", displsy: false}
  ]
};
var gitalk = new Gitalk({
  clientID: '2e02b4121096f7e6062f',
  clientSecret: 'aa5821b36a26ded29caa6b2c1289d450d8a2f9d8',
  repo: 'My-Blog-Comments',
  owner: 'wxuyuan',
  admin: ['wxuyuan'],
  id: document.title,
  distractionFreeMode: false
});
function addProperty(obj, propertyName, propertyvalue) {
  let desc = defaultDesc;
  desc.value = propertyvalue;
  Object.defineProperty(obj, propertyName, desc);
  return obj;
}
function getAttrs() {
  let ret = {};
  let attrs = location.href.split("?")[1].split("&");
  for (let id in attrs) {
    ret = addProperty(ret, attrs[id].split("=")[0], attrs[id].split("=")[1]);
  }
  return ret;
}
function rendTypewriter() {
  $(".typewriter").each(function() {
    let str = '<span class="typewriter-text" data-text="' + $(this).attr("data-text") +  '"></span>';
    console.log($(this).attr("data-text"));
    str += '<span class="typewriter-cursor">|</span>';
    console.log(this.nodeName);
    console.log($(this).html());
    $(this).removeAttr("data-text");
    $(this).html(str);
  });
  setInterval(() => {
    $(".typewriter-text").each(function() {
      let nowlen = $(this).text().length + 1;
      let data = $(this).attr("data-text");
      if (nowlen > data.length) {
        nowlen--;
      }
      $(this).html(data.substring(0, nowlen));
    });
  }, 200);
  setInterval(() => {
    $(".typewriter-cursor").each(function() {
      if ($(this).text() !== '|') {
        $(this).text('|');
      } else {
        $(this).html('&nbsp');
      }
    });
  }, 500);
}
function getBlogs() {
  $.ajax({
    method: "get",
    url: "/blog/blog.json",
    success: function(data) {
      console.log("BlogsData", data);
      rendBlogs(data);
    },
    error: function() {
      alert("请检查网络");
      getBlogs();
    }
  });
}
function getBlog(id, lastData = {}, getWhat = "ini") {
  if (getWhat === "ini") {
    $.ajax({
      method: "get",
      url: "/blog/" + id + "/ini.json",
      success: function(data) {
        console.log("Blog %d ini", id, data);
        getBlog(id, data, "content");
      },
      error: function() {
        alert("请检查网络");
        getBlog(id, data, "ini");
      }
    });
  } else {
    $.ajax({
      method: "get",
      url: "/blog/" + id + "/content.md",
      success: function(data) {
        console.log("Blog %d content", id, data);
        rendArtical(lastData, data);
      },
      error: function() {
        alert("请检查网络");
        getBlog(id, data, "content");
      }
    });
  }
}
function rendBlogs(ini) {
  for (let blogId in ini.blogs) {
    let blog = ini.blogs[blogId];
    $(".blogs-table tbody").each(function() {
      let str = "<tr><td><button class=\"btn btn-small\" onclick=\"location.href='/blog/?id=" + blogId + "'\">" + blog.title + "</button></td><td>";
      for (id in blog.tags) {
        str = str + "<kbd>" + blog.tags[id] + "</kbd>&nbsp;";
      }
      str = str + "</td><td>";
      for (id in blog.classes) {
        str = str + "<kbd>" + blog.classes[id] + "</kbd>&nbsp;";
      }
      str = str + "</td>";
      $(this).append(str);
    })
  }
}
function getSolutions() {
  $.ajax({
    method: "get",
    url: "/solution/solution.json",
    success: function(data) {
      console.log("SolutionsData", data);
      rendSolutions(data);
    },
    error: function() {
      alert("请检查网络");
      getSolutions();
    }
  });
}
function getSolution(id, lastData = {}, getWhat = "ini") {
  if (getWhat === "ini") {
    $.ajax({
      method: "get",
      url: "/solution/" + id + "/ini.json",
      success: function(data) {
        console.log("Solution %d ini", id, data);
        getSolution(id, data, "content");
      },
      error: function() {
        alert("请检查网络");
        getSolution(id, data, "ini");
      }
    });
  } else {
    $.ajax({
      method: "get",
      url: "/solution/" + id + "/content.md",
      success: function(data) {
        console.log("Solution %d content", id, data);
        rendArtical(lastData, data);
      },
      error: function() {
        alert("请检查网络");
        getSolution(id, data, "content");
      }
    });
  }
}
function rendSolutions(ini) {
  for (let solutionId in ini.solutions) {
    let solution = ini.solutions[solutionId];
    $(".solutions-table tbody").each(function() {
      let str = "<tr><td><button class=\"btn btn-small\" onclick=\"location.href='/solution/?id=" + solutionId + "'\">" + solution.title + "</button></td><td>";
      for (id in solution.tags) {
        str = str + "<kbd>" + solution.tags[id] + "</kbd>&nbsp;";
      }
      str = str + "</td><td>";
      for (id in solution.classes) {
        str = str + "<kbd>" + solution.classes[id] + "</kbd>&nbsp;";
      }
      str = str + "</td>";
      $(this).append(str);
    })
  }
}
function rendArtical(ini, artical) {
  $("head title").each(function() {
    let str = $(this).text();
    $(this).text(str + ini.title);
  });
  $(".artical .title").each(function() {
    $(this).text(ini.title);
  });
  $(".artical .content").each(function() {
    $(this).html(rendMarkdown(artical));
    renderMathInElement(this, katexConfig);
  });
}
function rendMarkdown(str) {
  return marked.marked(str);
}
function getProblemINI(id, blogNumbers) {
  $.ajax({
    method: "get",
    url: "/problem/" + id + "/ini.json",
    success: function(data) {
      console.log("Problem %d ini", id, data);
      rendProblemInProblems(data);
      if (id < blogNumbers - 1) {
        getProblemINI(id + 1, blogNumbers);
      }
    },
    error: function() {
      alert("请检查网络");
      getProblemINI(id, blogNumbers);
    }
  });
}
function getProblems() {
  $.ajax({
    method: "get",
    url: "/problem/ini.json",
    success: function(data) {
      console.log("Problem Numbers:", data);
      getProblemINI(0, data);
    },
    error: function() {
      alert("请检查网络");
      getProblems();
    }
  });
}
function rendProblemInProblems(data) {
  let str = "<tr><td>" + data.title;
  if (data.filesIO) {
    str += " (" + data.filesIO + ")";
  }
  str += '</td><td><div class="algorithm-tags">';
  for (let tag in data.algorithmTags) {
    str += "<kbd>" + data.algorithmTags[tag] + "</kbd>&nbsp;";
  }
  str += '</div><div class="time-sources-tags">';
  for (let tag in data.timeTags) {
    str += "<kbd>" + data.timeTags[tag] + "</kbd>&nbsp;";
  }
  for (let tag in data.sourceTags) {
    str += "<kbd>" + data.sourceTags[tag] + "</kbd>&nbsp;";
  }
  str += "</div></td></tr>";
  $(".problems-table tbody").append(str);
  $(".problems-table tbody : last-")
}
function rendGitalk() {
  gitalk.render('gitalk-container');
}
