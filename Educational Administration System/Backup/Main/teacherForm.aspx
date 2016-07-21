<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="teacherForm.aspx.cs" Inherits="Main.TeacherForm" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>教务管理系统</title>
    <link href="css/style.css" type="text/css" rel="stylesheet" />
</head>
<body>
    <div style="float:left;width:100%;background-image:url(/images/head_bg.gif);background-repeat:repeat-x;">
        <img src="/images/logo_school.png"/><img src="/images/logo_jw.png"/>
        <div style="float:right">
        <img src="/images/info_bg.gif" />
        </div>
    </div>
    <form id="form1" runat="server">
    <div id="head">
        <asp:Button ID="Button1" runat="server" Text="学生成绩查询" class="button" 
            onclick="Button1_Click"/>
        <asp:Button ID="Button2" runat="server" Text="录入学生成绩" class="button" 
            onclick="Button2_Click" />
        <asp:Button ID="Button3" runat="server" Text="修改密码" class="button" 
            onclick="Button3_Click"/>


    </div>
    <asp:MultiView ID="MultiView1" runat="server">
        <asp:View ID="View1" runat="server">
        <asp:Button ID="Button4" runat="server" onclick="Button4_Click" Text="查询所有课程" class="button"/>
            <asp:DropDownList ID="DropDownList1" runat="server">
            </asp:DropDownList>
        <asp:Button ID="Button5" runat="server" onclick="Button5_Click" Text="查询选定课程" class="button"/>
            <asp:GridView ID="GridView1" runat="server" CellPadding="4" ForeColor="#333333" 
                GridLines="None">
                <AlternatingRowStyle BackColor="White" />
                <EditRowStyle BackColor="#2461BF" />
                <FooterStyle BackColor="#507CD1" Font-Bold="True" ForeColor="White" />
                <HeaderStyle BackColor="#507CD1" Font-Bold="True" ForeColor="White" />
                <PagerStyle BackColor="#2461BF" ForeColor="White" HorizontalAlign="Center" />
                <RowStyle BackColor="#EFF3FB" />
                <SelectedRowStyle BackColor="#D1DDF1" Font-Bold="True" ForeColor="#333333" />
                <SortedAscendingCellStyle BackColor="#F5F7FB" />
                <SortedAscendingHeaderStyle BackColor="#6D95E1" />
                <SortedDescendingCellStyle BackColor="#E9EBEF" />
                <SortedDescendingHeaderStyle BackColor="#4870BE" />
            </asp:GridView>
        </asp:View>
        <asp:View ID="View2" runat="server">
        <asp:DropDownList ID="DropDownList2" runat="server" AutoPostBack="True" 
                onselectedindexchanged="DropDownList2_SelectedIndexChanged">
            </asp:DropDownList>
        <asp:DropDownList ID="DropDownList3" runat="server" AutoPostBack="True" 
                onselectedindexchanged="DropDownList3_SelectedIndexChanged">
            </asp:DropDownList>
            <asp:Label ID="Label1" runat="server"></asp:Label>
        <asp:TextBox ID="TextBox1" runat="server"></asp:TextBox>
            <asp:Button ID="Button6" runat="server" Text="确认" class="button" 
                onclick="Button6_Click"/>
        </asp:View>
        <asp:View ID="View3" runat="server">
            输入旧密码<asp:TextBox ID="TextBox2" runat="server"></asp:TextBox>
            <asp:Label ID="Label2" runat="server"></asp:Label>
            <br />
            输入新密码<asp:TextBox ID="TextBox3" runat="server"></asp:TextBox>
            <asp:Label ID="Label3" runat="server"></asp:Label>
            <br />
            确认新密码<asp:TextBox ID="TextBox4" runat="server"></asp:TextBox><br />
            <asp:Button ID="Button7" runat="server" Text="提交" class="button" onclick="Button7_Click"/>
        </asp:View>
    </asp:MultiView>
    </form>
</body>
</html>
