<%@ page contentType="text/html;charset=UTF-8"%>
<html>
<head>
	<title>登陆</title>
</head>
<body>
<center>
	<h1>留言管理</h1>
	<hr>
	<br>
	<%
		if(session.getAttribute("uname")!=null)
		{
			// 用户已登陆
	%>
	<form action="insert_do.jsp" method="post">
		<table>
			<tr>
				<td colspan="2">添加新留言</td>
			</tr>
			<tr>
				<td>标题：</td>
				<td><input type="text" name="title"></td>
			</tr>
			<tr>
				<td>作者：</td>
				<td><input type="text" name="author"></td>
			</tr>
			<tr>
				<td>内容：</td>
				<td><textarea name="content" cols="30" rows="6"></textarea></td>
			</tr>
			<tr>
				<td colspan="2">
					<input type="submit" value="添加">
					<input type="reset" value="重置">
				</td>
			</tr>
		</table>
	</form>
	<h3><a href="list_notes.jsp">回到留言列表页</a></h3>
	<%
		}
		else
		{
			// 用户未登陆，提示用户登陆，并跳转
			response.setHeader("refresh","2;URL=login.jsp") ;
	%>
			您还未登陆，请先登陆！！！<br>
			两秒后自动跳转到登陆窗口！！！<br>
			如果没有跳转，请按<a href="login.jsp">这里</a>！！！<br>
	<%
		}
	%>
</center>
</body>
</html>