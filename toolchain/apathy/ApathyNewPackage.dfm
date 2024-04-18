object frmNewPackage: TfrmNewPackage
  Left = 349
  Top = 260
  Width = 343
  Height = 234
  Caption = 'Compile Tag Packge'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 12
    Width = 37
    Height = 13
    Caption = 'Name:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object edtPackName: TEdit
    Left = 48
    Top = 8
    Width = 185
    Height = 21
    TabOrder = 0
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 48
    Width = 225
    Height = 145
    Caption = 'Include Types: '
    TabOrder = 1
    object CheckBox1: TCheckBox
      Left = 16
      Top = 16
      Width = 49
      Height = 17
      Caption = 'ablm'
      Checked = True
      State = cbChecked
      TabOrder = 0
    end
    object CheckBox2: TCheckBox
      Left = 16
      Top = 32
      Width = 49
      Height = 17
      Caption = 'ablp'
      Checked = True
      State = cbChecked
      TabOrder = 1
    end
    object CheckBox3: TCheckBox
      Left = 16
      Top = 48
      Width = 49
      Height = 17
      Caption = 'army'
      Checked = True
      State = cbChecked
      TabOrder = 2
    end
    object CheckBox4: TCheckBox
      Left = 16
      Top = 64
      Width = 49
      Height = 17
      Caption = 'char'
      Checked = True
      State = cbChecked
      TabOrder = 3
    end
    object CheckBox5: TCheckBox
      Left = 16
      Top = 80
      Width = 49
      Height = 17
      Caption = 'cphy'
      Checked = True
      State = cbChecked
      TabOrder = 4
    end
    object CheckBox6: TCheckBox
      Left = 16
      Top = 96
      Width = 49
      Height = 17
      Caption = 'intf'
      Checked = True
      State = cbChecked
      TabOrder = 5
    end
    object CheckBox7: TCheckBox
      Left = 16
      Top = 112
      Width = 49
      Height = 17
      Caption = 'mech'
      Checked = True
      State = cbChecked
      TabOrder = 6
    end
    object CheckBox8: TCheckBox
      Left = 88
      Top = 16
      Width = 49
      Height = 17
      Caption = 'obje'
      Checked = True
      State = cbChecked
      TabOrder = 7
    end
    object CheckBox11: TCheckBox
      Left = 88
      Top = 48
      Width = 49
      Height = 17
      Caption = 'proj'
      Checked = True
      State = cbChecked
      TabOrder = 8
    end
    object CheckBox12: TCheckBox
      Left = 88
      Top = 80
      Width = 49
      Height = 17
      Caption = 'scri'
      Checked = True
      State = cbChecked
      TabOrder = 9
    end
    object CheckBox13: TCheckBox
      Left = 88
      Top = 64
      Width = 49
      Height = 17
      Caption = 'scen'
      Checked = True
      State = cbChecked
      TabOrder = 10
    end
    object CheckBox15: TCheckBox
      Left = 88
      Top = 32
      Width = 49
      Height = 17
      Caption = 'pgrp'
      Checked = True
      State = cbChecked
      TabOrder = 11
    end
    object CheckBox10: TCheckBox
      Left = 88
      Top = 96
      Width = 49
      Height = 17
      Caption = 'sndc'
      Checked = True
      State = cbChecked
      TabOrder = 12
    end
    object CheckBox16: TCheckBox
      Left = 88
      Top = 112
      Width = 49
      Height = 17
      Caption = 'sndm'
      Checked = True
      State = cbChecked
      TabOrder = 13
    end
    object CheckBox17: TCheckBox
      Left = 160
      Top = 48
      Width = 49
      Height = 17
      Caption = 'text'
      Checked = True
      State = cbChecked
      TabOrder = 14
    end
    object CheckBox18: TCheckBox
      Left = 160
      Top = 16
      Width = 49
      Height = 17
      Caption = 'sndu'
      Checked = True
      State = cbChecked
      TabOrder = 15
    end
    object CheckBox19: TCheckBox
      Left = 160
      Top = 64
      Width = 49
      Height = 17
      Caption = 'tmap'
      Checked = True
      State = cbChecked
      TabOrder = 16
    end
    object CheckBox20: TCheckBox
      Left = 160
      Top = 32
      Width = 49
      Height = 17
      Caption = 'sprc'
      Checked = True
      State = cbChecked
      TabOrder = 17
    end
    object CheckBox21: TCheckBox
      Left = 160
      Top = 80
      Width = 49
      Height = 17
      Caption = 'unit'
      Checked = True
      State = cbChecked
      TabOrder = 18
    end
    object CheckBox22: TCheckBox
      Left = 160
      Top = 96
      Width = 49
      Height = 17
      Caption = 'wthr'
      Checked = True
      State = cbChecked
      TabOrder = 19
    end
  end
  object btnCompile: TButton
    Left = 248
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Compile'
    Default = True
    TabOrder = 2
    OnClick = btnCompileClick
  end
  object btnCancel: TButton
    Left = 248
    Top = 40
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    TabOrder = 3
    OnClick = btnCancelClick
  end
end
