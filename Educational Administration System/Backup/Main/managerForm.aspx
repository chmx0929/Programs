<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="managerForm.aspx.cs" Inherits="Main.managerForm" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>教务管理系统</title>
    <link href="css/style.css" type="text/css" rel="stylesheet" />
</head>
<body>
    <div id="head">
        <img src="/images/logo_school.png"/><img src="/images/logo_jw.png"/>
        <div style="float:right">
        <img src="/images/info_bg.gif" />
        </div>
    </div>
    <form id="form1" runat="server">
    <div style="background-image:url(/images/nav_bg.gif);background-repeat:repeat-x;clear:both;width:100%">
        <asp:Button ID="Button1" runat="server" Text="教师信息管理" class="button" 
            onclick="Button1_Click"/>
        <asp:Button ID="Button2" runat="server" Text="学生信息管理" class="button" 
            onclick="Button2_Click" />
        <asp:Button ID="Button3" runat="server" Text="修改密码" class="button" 
            onclick="Button3_Click"/>
    </div>
    <asp:MultiView ID="MultiView1" runat="server">
        <asp:View ID="View1" runat="server">
        <div style="background-image:url(/images/nav_bg.gif);background-repeat:repeat-x;clear:both;width:100%">
        <asp:Button ID="Button4" runat="server" onclick="Button4_Click" Text="查询教师信息" class="button"/>
        <asp:Button ID="Button5" runat="server" onclick="Button5_Click" Text="添加教师信息" class="button"/>
        <asp:Button ID="Button6" runat="server" onclick="Button6_Click" Text="修改教师信息" class="button"/>
        <asp:Button ID="Button7" runat="server" onclick="Button7_Click" Text="删除教师信息" class="button"/>
        </div>
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
        <asp:MultiView ID="MultiView2" runat="server">
            <asp:View ID="View4" runat="server">
            账号<asp:TextBox ID="TextBox2" runat="server"></asp:TextBox><br/>
            姓名<asp:TextBox ID="TextBox3" runat="server"></asp:TextBox><br/>
            密码<asp:TextBox ID="TextBox4" runat="server"></asp:TextBox><br/>
            <asp:Button ID="Button8" runat="server" Text="确认" class="button" 
                    onclick="Button8_Click" Height="28px"/>
            </asp:View>
            <asp:View ID="View5" runat="server">
            <asp:DropDownList ID="DropDownList1" runat="server">
            </asp:DropDownList>
                <br />
                <asp:TextBox ID="TextBox8" runat="server"></asp:TextBox>
                <br />
                <asp:TextBox ID="TextBox9" runat="server"></asp:TextBox>
                <br />
                <asp:Button ID="Button15" runat="server" Text="确认" class="button" 
                    onclick="Button15_Click"/>
            </asp:View>
            <asp:View ID="View6" runat="server">
                <asp:DropDownList ID="DropDownList2" runat="server" AutoPostBack="True" 
                    onselectedindexchanged="DropDownList2_SelectedIndexChanged">
                </asp:DropDownList>
                <asp:Label ID="Label1" runat="server"></asp:Label>
                <br />
                <asp:Button ID="Button14" runat="server" Text=" 确认 " class="button" 
                    onclick="Button14_Click"/>
            </asp:View>
        </asp:MultiView>
        </asp:View>
        <asp:View ID="View2" runat="server">
           <div style="background-image:url(/images/nav_bg.gif);background-repeat:repeat-x;clear:both;width:100%">
            <asp:Button ID="Button10" runat="server" Text="查询学生信息" class="button" 
                   onclick="Button10_Click"/>
            <asp:Button ID="Button11" runat="server" Text="添加学生信息" class="button" onclick="Button11_Click"/>
            <asp:Button ID="Button12" runat="server" Text="修改学生信息" class="button" onclick="Button12_Click"/>
            <asp:Button ID="Button13" runat="server" Text="删除学生信息" class="button" onclick="Button13_Click"/>
            </div>
            <asp:GridView ID="GridView2" runat="server" CellPadding="4" ForeColor="#333333" 
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
           
            <asp:MultiView ID="MultiView3" runat="server">
                <asp:View ID="View7" runat="server">
                 账号<asp:TextBox ID="TextBox1" runat="server"></asp:TextBox><br/>
                 姓名<asp:TextBox ID="TextBox11" runat="server"></asp:TextBox><br/>
                 密码<asp:TextBox ID="TextBox12" runat="server"></asp:TextBox><br/>
            <asp:Button ID="Button16" runat="server" Text="确认" class="button" 
                        onclick="Button16_Click"/>
                </asp:View>
                <asp:View ID="View8" runat="server">
                <asp:DropDownList ID="DropDownList4" runat="server">
                </asp:DropDownList>
                <br />
                <asp:TextBox ID="TextBox13" runat="server"></asp:TextBox>
                <br />
                <asp:TextBox ID="TextBox14" runat="server"></asp:TextBox>
                <br />
                <asp:Button ID="Button17" runat="server" Text="确认" class="button" 
                        onclick="Button17_Click"/>
                </asp:View>
                <asp:View ID="View9" runat="server">
                <asp:DropDownList ID="DropDownList3" runat="server" AutoPostBack="True" 
                        onselectedindexchanged="DropDownList3_SelectedIndexChanged">
                </asp:DropDownList>
                <asp:Label ID="Label2" runat="server"></asp:Label>
                <br />
                <asp:Button ID="Button18" runat="server" Text=" 确认 " class="button" 
                        onclick="Button18_Click"/>
                </asp:View>
            </asp:MultiView>
           
        </asp:View>
        <asp:View ID="View3" runat="server">
            输入旧密码<asp:TextBox ID="TextBox5" runat="server"></asp:TextBox>
            <asp:Label ID="Label4" runat="server"></asp:Label>
            <br />
            输入新密码<asp:TextBox ID="TextBox6" runat="server"></asp:TextBox>
            <asp:Label ID="Label5" runat="server"></asp:Label>
            <br />
            确认新密码<asp:TextBox ID="TextBox7" runat="server" Height="19px"></asp:TextBox><br />
            <asp:Button ID="Button9" runat="server" Text="提交" onclick="Button9_Click" 
                class="button"/>
        </asp:View>
    </asp:MultiView>
    </form>
</body>
</html>
