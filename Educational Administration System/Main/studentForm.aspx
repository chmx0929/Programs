<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="studentForm.aspx.cs" Inherits="Main.StudentForm" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <title>教务管理系统</title>
    <link href="css/style.css" type="text/css" rel="stylesheet" />
</head>
<body>
    <form id="form1" runat="server">
    <div id="head" >
        <img src="/images/logo_school.png"/><img src="/images/logo_jw.png"/>
        <div style="float:right">
        <img src="/images/info_bg.gif" />
        </div>
    </div>
    <div id="nav">
        <asp:Button ID="Button2" runat="server" Text="成绩查询" class="button" 
            onclick="Button2_Click"/>
        <asp:Button ID="Button3" runat="server" Text="选课" class="button" 
            onclick="Button3_Click" />
        <asp:Button ID="Button4" runat="server" Text="修改密码" class="button" 
            onclick="Button4_Click"/>
    </div>

    <asp:MultiView ID="MultiView1" runat="server">       
        <asp:View ID="View1" runat="server">
        <asp:GridView ID="GridView1" runat="server" AllowPaging="True" AllowSorting="True" 
                CellPadding="4" ForeColor="#333333" GridLines="None">
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
            <asp:CheckBoxList ID="CheckBoxList1" runat="server">
            </asp:CheckBoxList>
            <asp:Button ID="Button5" runat="server" Text="提交" class="button" 
                onclick="Button5_Click" />

        </asp:View>
        <asp:View ID="View3" runat="server">
            输入旧密码<asp:TextBox ID="TextBox5" runat="server"></asp:TextBox>
            <asp:Label ID="Label4" runat="server"></asp:Label>
            <br />
            输入新密码<asp:TextBox ID="TextBox6" runat="server"></asp:TextBox>
            <asp:Label ID="Label5" runat="server"></asp:Label>
            <br />
            确认新密码<asp:TextBox ID="TextBox7" runat="server"></asp:TextBox><br />
            <asp:Button ID="Button1" runat="server" onclick="Button1_Click" Text="提交"
                class="button"  />
        </asp:View>
    </asp:MultiView>
    </form>
    </body>
</html>
