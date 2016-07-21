<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Login.aspx.cs" Inherits="Main.Login" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>教务管理系统</title>
    <style type="text/css">
        body
        {
            background-image: url(/images/login_bg.jpg);
            background-repeat: repeat-x;
            }
        #logo
        {
            margin-top:42px;
            width:888px;
            margin-left:auto;
            margin-right:auto;
         }
         #main
        {
            margin-left:auto;
            margin-right:auto;
            width:888px;
            margin-top:10px;
            }
        #main_left
        {
            width:426px;
            background-image: url(/images/login_left.jpg);
            background-position:0 0;
            float:left;
            }
        #main_left img
        {
            padding-top:30px;
            }
        #main_right
        {
            width:462px;
            height:340px;
            background-image: url(/images/login_right.jpg);
            background-position:0 0;
            float:left;   
            }
        #form1
        {
            padding-left:100px;
            padding-top:100px;
            }       
    </style>
</head>
<body>
    <div id="logo">
        <img src="images/logo_school.png"/><img src="images/logo_jw.png"/>
    </div>
    <div id="main">
    <div id="main_left"> 
        <img src="images/login_pic.png"/>
    </div>
    <div id="main_right">
        <form id="form1" runat="server">
        用户名：<asp:TextBox ID="ID" runat="server"></asp:TextBox><br/>
        密&nbsp&nbsp;码：<asp:TextBox ID="Password" runat="server" TextMode="Password"></asp:TextBox>
        <asp:RadioButtonList ID="identity" runat="server">
        <asp:ListItem Value="manager">Manager</asp:ListItem>
        <asp:ListItem Value="teacher">Teacher</asp:ListItem>
        <asp:ListItem Selected="True" Value="student">Student</asp:ListItem>
        </asp:RadioButtonList>
        <asp:Button ID="submit" runat="server" onclick="submit_Click" Text="Login" />
    </form>
    </div>
    </div>

    
</body>
</html>
