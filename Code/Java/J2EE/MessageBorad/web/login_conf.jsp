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
	<%!
		String dbURL = "jdbc:derby://localhost:1527/Message;create=true;user=Administrator;password=admin";
		Connection conn	 = null ;
		PreparedStatement pstmt	= null ;
		ResultSet rs = null ;
	%>
	<%
		// 声明一个boolean变量，用于保存用户是否合法的状态
		boolean flag = false ;

		// 接收参数
		String name = request.getParameter("name") ;
		String password = request.getParameter("password") ;
	%>
	<%
		String sql = "SELECT name FROM person WHERE name=? and password=?" ;
		try
		{
			Class.forName("org.apache.derby.jdbc.ClientDriver").newInstance();
			conn = DriverManager.getConnection(dbURL) ;
			pstmt = conn.prepareStatement(sql) ;
			pstmt.setString(1, name) ;
			pstmt.setString(2, password) ;
			rs = pstmt.executeQuery() ;
			if(rs.next())
			{
				// 用户合法
				flag = true ;
				// 将用户名保存在session之中
				session.setAttribute("uname", rs.getString(1)) ;
			}
			else
			{
				// 保存错误信息
				request.setAttribute("err", "错误的用户名及密码！") ;
			}
			rs.close() ;
			pstmt.close() ;
			conn.close() ;
		}
		catch(Exception e)
		{log(e.toString());}
	%>
	<%
		// 跳转
		if(flag)
		{
			// 用户合法
	%>
			<jsp:forward page="login_success.jsp"/>
	<%
		}
		else
		{
			// 用户非法
	%>
			<jsp:forward page="login.jsp"/>
	<%
		}
	%>
</center>
</body>
</html>