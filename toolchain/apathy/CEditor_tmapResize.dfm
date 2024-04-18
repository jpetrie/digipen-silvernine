object frmTMAP_Resize: TfrmTMAP_Resize
  Left = 431
  Top = 335
  ActiveControl = edtWidth
  AutoScroll = False
  Caption = 'Resize Map'
  ClientHeight = 135
  ClientWidth = 245
  Color = clBtnFace
  Constraints.MaxHeight = 162
  Constraints.MaxWidth = 253
  Constraints.MinHeight = 162
  Constraints.MinWidth = 253
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 20
    Top = 12
    Width = 38
    Height = 13
    Caption = 'Width:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 16
    Top = 36
    Width = 42
    Height = 13
    Caption = 'Height:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object btnCancel: TButton
    Left = 160
    Top = 40
    Width = 73
    Height = 25
    Caption = 'Cancel'
    TabOrder = 0
    OnClick = btnCancelClick
  end
  object btnResize: TButton
    Left = 160
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Resize'
    TabOrder = 1
    OnClick = btnResizeClick
  end
  object edtWidth: TEdit
    Left = 64
    Top = 8
    Width = 73
    Height = 21
    TabOrder = 2
    Text = '0'
  end
  object edtHeight: TEdit
    Left = 64
    Top = 32
    Width = 73
    Height = 21
    TabOrder = 3
    Text = '0'
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 64
    Width = 129
    Height = 65
    Caption = 'Existing Tiles: '
    TabOrder = 4
    object radPreserve: TRadioButton
      Left = 8
      Top = 16
      Width = 113
      Height = 17
      Caption = 'Preserve Data'
      Checked = True
      TabOrder = 0
      TabStop = True
    end
    object radNukeAndPave: TRadioButton
      Left = 8
      Top = 40
      Width = 113
      Height = 17
      Caption = 'Nuke and Pave'
      TabOrder = 1
    end
  end
end
