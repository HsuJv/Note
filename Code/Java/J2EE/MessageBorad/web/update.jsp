<%@ page contentType="text/html;charset=UTF-8"%>
<%@ page import="java.sql.*"%>
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
	<%!
		String dbURL = "jdbc:derby://localhost:1527/Message;create=true;user=Administrator;password=admin";
		Connection conn	 = null ;
		PreparedStatement pstmt	= null ;
		ResultSet rs = null ;
	%>
	<%
		// 接收参数
		int id = 0 ;
		try
		{
			id = Integer.parseInt(request.getParameter("id")) ;
		}
		catch(Exception e)
		{}
	%>
	<%
		// 如果有内容，则修改变量i，如果没有，则根据i的值进行无内容提示
		int i = 0 ;
		String sql = "SELECT id,title,author,content FROM message WHERE id=?" ;
		try
		{
			Class.forName("org.apache.derby.jdbc.ClientDriver").newInstance();
			conn = DriverManager.getConnection(dbURL) ;
			pstmt = conn.prepareStatement(sql) ;
			// 设置查询条件
			pstmt.setInt(1, id) ;
			rs = pstmt.executeQuery() ;
	%>
	<%
			if(rs.next())
			{
				i++ ;
				// 进行循环打印，打印出所有的内容，以表格形式
				// 从数据库中取出内容
				id = rs.getInt(1) ;
				String title = rs.getString(2) ;
				String author = rs.getString(3) ;
				String content = rs.getString(4) ;
	%>
	<form action="update_do.jsp" method="post">
		<table>
			<tr>
				<td colspan="2">添加新留言</td>
			</tr>
			<tr>
				<td>标题：</td>
				<td><input type="text" name="title" value="<%=title%>"></td>
			</tr>
			<tr>
				<td>作者：</td>
				<td><input type="text" name="author" value="<%=author%>"></td>
			</tr>
			<tr>
				<td>内容：</td>
				<td><textarea name="content" cols="30" rows="6"><%=content%></textarea></td>
			</tr>
			<tr>
				<td colspan="2">
					<input type="hidden" name="id" value="<%=id%>">
					<input type="submit" value="更新">
					<input type="reset" value="重置">
				</td>
			</tr>
		</table>
	</form>
	<%
			}
			else
			{
	%>
				没有发现，要更新的内容！！<br>
				请确认要更新的留言是否存在！！<br>
	<%
			}
	%>
	<%
			rs.close() ;
			pstmt.close() ;
			conn.close() ;
		}
		catch(Exception e)
		{}
	%>
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