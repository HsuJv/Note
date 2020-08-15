<%-- 
    Document   : newword
    Created on : 2018-6-24, 12:38:38
    Author     : aasus
--%>

<%@page import="Model.Words"%>
<%@page import="Model.Account"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>编辑新帖</title>

        <style type="text/css">
            .word_wrap{
                width: 960px;
                margin: 40px auto;
            }
            .btn_b{
                cursor: pointer;
                border-radius: 2px;
                -webkit-border-radius: 2px;
                -moz-border-radius: 2px;
                -khtml-border-radius: 2px;
                padding: 0 15px;
                height: 32px;
                line-height: 30px;
                background-color: #CA0C16;
                border: 1px solid #B50A13;
                color: #fff !important;
                font-size: 14px;
            }
            .bbs_editor{
                background: #fff;
                padding: 24px;
                box-shadow: 0 2px 4px 0 rgba(0,0,0,.05);
                border-width: 1;
            }
            .word_t_l{
                width: 680px;
                height: 32px;
                border: 1px solid #ccc;
                border-radius: 2px;
                position: relative;
            }
            .word_title{
                padding: 0 8px;
                height: 30px;
                width: 450px;
                line-height: 30px;
                border: none;
                outline: 0;
            }
            .word_b{
                width: 100%;
                background-color: #fff;
                box-shadow: 0 2px 4px 0 rgba(0,0,0,.05);
                margin: 8px 0;
            }
            .comt{
                display: block;
                padding: 20px 10px;
                margin-top: 10px;
                border: 1px solid #A9CBEE;
            }

            .word_body{
                margin: 0 5px 0 0;
                padding: 5px;
                border: 1px solid #ccc;
                color: #333;
                outline: 0;
                width: 99%;
                clear: both;
                line-height: 18px;
                resize: none;
                vertical-align: top;
                height: 184px;
            }
            .pub_ml {
                margin-left: 95px;
            }
            .pub_list {
                padding: 10px;
                margin: 10px 0;
                width: 460px;
                border: 1px dashed #d6d6d6;
                margin-left: 95px;
            }
            .pub_list li{
                position: relative;
                line-height: 24px;
                font-size: 12px;
                color: #000;
                padding-left: 10px;
                list-style: none;
            }
        </style>
    </head>
    <body>
        <div class="topNav">
            <jsp:include page="/top.jsp"></jsp:include>
            </div>
            <div class="word_wrap">
                <div id="editor" class="bbs_editor">
                    <form id="new_word" class="new_word" action="./SendWordServlet">
                        <div class="word_b">
                            <div class="comt">
                                <div class="editor">
                                    <textarea name="word_content" class="word_body" cols="20" rows="10" maxlength="300" placeholder="请输入内容"></textarea>
                                </div>
                            </div>
                        </div>
                    <%
                        long object = Long.parseLong(request.getParameter("object"));
                    %>
                    <input name="new_word_object" type="text" hidden="hidden" value="<%=object%>">
                    <div class="pub_ml">
                        <input  value="发送" class="btn_b" type="submit">
                    </div>
                    <ul class="pub_list pub_ml">
                        <li>请遵守用户行为准则，不得违反国家法律法规。</li>
                        <li>为了维护良好的技术讨论环境，请不要讨论政治 相关话题。</li>
                        <li>富强、民主、文明、和谐</li>
                        <li>自由、平等、公正、法治</li>
                        <li>爱国、敬业、诚信、友善</li>
                    </ul>
                </form>
            </div>
        </div>
    </body>
</html>
