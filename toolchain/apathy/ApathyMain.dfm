object frmMain: TfrmMain
  Left = 990
  Top = 195
  AlphaBlendValue = 200
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Apathy Editor'
  ClientHeight = 584
  ClientWidth = 282
  Color = clBtnFace
  DockSite = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = mnuApathy
  OldCreateOrder = False
  Visible = True
  PixelsPerInch = 96
  TextHeight = 13
  object treeTagList: TTreeView
    Left = 0
    Top = 40
    Width = 282
    Height = 544
    Align = alBottom
    Indent = 19
    PopupMenu = popTagList
    ReadOnly = True
    RightClickSelect = True
    TabOrder = 0
    OnDblClick = treeTagListDblClick
  end
  object cmbBrowsePath: TComboBox
    Left = 8
    Top = 8
    Width = 241
    Height = 21
    ItemHeight = 13
    TabOrder = 1
  end
  object btnBrowse: TButton
    Left = 256
    Top = 8
    Width = 17
    Height = 21
    Caption = '...'
    TabOrder = 2
    OnClick = btnBrowseClick
  end
  object mnuApathy: TMainMenu
    Left = 8
    Top = 48
    object File1: TMenuItem
      Caption = '&File'
      object NewTag1: TMenuItem
        Caption = 'New Tag...'
        OnClick = NewTag1Click
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object Exit1: TMenuItem
        Caption = 'E&xit'
        OnClick = Exit1Click
      end
    end
    object Tag1: TMenuItem
      Caption = 'Tag'
      object Delete1: TMenuItem
        Caption = 'Delete'
        OnClick = Delete1Click
      end
      object Properties1: TMenuItem
        Caption = 'Properties...'
        OnClick = Properties1Click
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object CompilePackage1: TMenuItem
        Caption = 'Compile Package...'
        OnClick = CompilePackage1Click
      end
    end
    object Help1: TMenuItem
      Caption = '&Help'
      object About1: TMenuItem
        Caption = '&About...'
      end
    end
  end
  object popTagList: TPopupMenu
    Left = 40
    Top = 48
    object Delete2: TMenuItem
      Caption = 'Delete'
      OnClick = Delete1Click
    end
    object Properties2: TMenuItem
      Caption = 'Properties...'
      OnClick = Properties1Click
    end
  end
end
