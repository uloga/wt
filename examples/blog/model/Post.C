/*
 * Copyright (C) 2009 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */

#include <boost/lexical_cast.hpp>

#include "Post.h"
#include "Comment.h"
#include "User.h"
#include "Tag.h"
#include "Token.h"

#include <Wt/Dbo/Impl>
#include <ctype.h>

DBO_INSTANTIATE_TEMPLATES(Post);

std::string Post::permaLink() const
{
  return date.toString("yyyy/MM/dd/'" + titleToUrl() + '\'').toUTF8();
}

std::string Post::commentCount() const
{
  int count = (int)comments.size() - 1;
  if (count == 1)
    return "1 comment";
  else
    return boost::lexical_cast<std::string>(count) + " comments";
}

dbo::ptr<Comment> Post::rootComment() const
{
  if (session())
    return session()->find<Comment>()
      .where("post_id = ?").bind(id())
      .where("parent_id is null");
  else
    return dbo::ptr<Comment>();
}

std::string Post::titleToUrl() const
{
  std::string result = title.narrow();
  for (unsigned i = 0; i < result.length(); ++i) {
    if (!isalnum(result[i]))
      result[i] = '_';
    else
      result[i] = tolower(result[i]);
  }
  
  return result;
}
