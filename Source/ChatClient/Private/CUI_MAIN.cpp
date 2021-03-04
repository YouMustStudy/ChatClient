// Fill out your copyright notice in the Description page of Project Settings.
#include "CUI_MAIN.h"
#include "CUI_LOG.h"
#include "CUI_USER.h"
#include "ChatModule.h"

void UCUI_MAIN::RequestRoomList()
{
	//���� ������ ��û
	static FString roomListCommand = L"/roomlist";
	if (nullptr != chatModule)
	{
		chatModule->SendMsg(roomListCommand);
	}
}

void UCUI_MAIN::InputMsgBoxOnTextCommitted(const FText& InText, ETextCommit::Type InCommitType)
{
	if (ETextCommit::Type::OnEnter == InCommitType)
	{
		SendChat();
		inputMsgBox->SetKeyboardFocus();
	}
}

void UCUI_MAIN::NativeConstruct()
{
	Super::NativeConstruct();
	UserUIClass = ConstructorHelpersInternal::FindOrLoadClass(UserUIPath, UUserWidget::StaticClass());
	LogUIClass = ConstructorHelpersInternal::FindOrLoadClass(LogUIPath, UUserWidget::StaticClass());

	if(nullptr != sendButton)
		sendButton->OnClicked.AddDynamic(this, &UCUI_MAIN::SendChat);
	if(nullptr != roomButton)
		roomButton->OnClicked.AddDynamic(this, &UCUI_MAIN::RequestRoomList);
	if (nullptr != inputMsgBox)
		inputMsgBox->OnTextCommitted.AddDynamic(this, &UCUI_MAIN::InputMsgBoxOnTextCommitted);
}

void UCUI_MAIN::SetRoomName(const FString& name)
{
	//�̸� ����
	if (nullptr != roomNameText)
		roomNameText->SetText(FText::FromString(name));
}

void UCUI_MAIN::ClearInputMsgBox()
{
	//�Է¹ڽ� �ʱ�ȭ
	if (nullptr != inputMsgBox)
		inputMsgBox->SetText(FText::GetEmpty());
}

void UCUI_MAIN::SendChat()
{
	if (nullptr != inputMsgBox)
	{
		//������ �Է��� �޾� ������ ����.
		FString msg = inputMsgBox->GetText().ToString();
		if (false == msg.IsEmpty())
		{
			if (nullptr != chatModule)
			{
				chatModule->SendMsg(msg);
				inputMsgBox->SetText(FText::GetEmpty());
				inputMsgBox->SetKeyboardFocus();
			}
		}
	}
}

void UCUI_MAIN::SetInputMsgBox(const FString& msg)
{
	if (nullptr != inputMsgBox)
	{
		//�־��� ���ڿ��� �Է�â�� �ʱ�ȭ.
		inputMsgBox->SetText(FText::FromString(msg));
		inputMsgBox->SetKeyboardFocus();
	}
}

void UCUI_MAIN::AddChatLog(UPARAM(ref) const FString& msg, FLinearColor color)
{
	if (nullptr != chatBox)
	{
		//ä�� �αװ� MAX_CHAT_LOG�� �Ѿ�� �� �� ��ü�� ���� �� ����.
		int32 chatLogCnt = chatBox->GetChildrenCount();
		if (chatLogCnt >= MAX_CHAT_LOG)
			chatBox->RemoveChildAt(0);

		if (nullptr != UILogClass)
		{
			UCUI_LOG* UILog = CreateWidget<UCUI_LOG>(GetWorld(), LogUIClass);
			if (nullptr != UILog)
			{
				int32 curOffset = chatBox->GetScrollOffset();
				int32 endOffset = chatBox->GetScrollOffsetOfEnd();
				UILog->chatLog->SetText(FText::FromString(msg));
				FSlateColor clr{ color };
				UILog->chatLog->SetColorAndOpacity(clr);
				chatBox->AddChild(UILog);
				if (curOffset == endOffset)
					chatBox->ScrollToEnd();
			}
		}
	}
}

void UCUI_MAIN::ClearChatLog()
{
	//ä�÷α׸� �ʱ�ȭ
	if(nullptr != chatBox)
		chatBox->ClearChildren();
}

void UCUI_MAIN::AddUserBox(const FString& user)
{
	//������ ������Ͽ� �߰�
	if (nullptr != userBox)
	{
		if (false == userTable.Contains(user))
		{
			if (nullptr != UserUIClass)
			{
				UCUI_USER* newUserUI = CreateWidget<UCUI_USER>(GetWorld(), UserUIClass);
				if (nullptr != newUserUI)
				{
					newUserUI->uiMain = this;
					newUserUI->SetName(user);
					userTable.Emplace(user, newUserUI);
					userBox->AddChild(newUserUI);
				}
			}
		}
	}
}

void UCUI_MAIN::RemoveUserBox(const FString& user)
{
	//������ ������Ͽ��� ����
	if (nullptr != userBox)
	{
		if (true == userTable.Contains(user))
		{
			UCUI_USER* removeUser = nullptr;
			if (true == userTable.RemoveAndCopyValue(user, removeUser))
				userBox->RemoveChild(removeUser);
		}
	}
}

void UCUI_MAIN::RefreshUserBox(UPARAM(ref) const TArray<FString>& users)
{
	if (nullptr != userBox)
	{
		//���� ����� �ʱ�ȭ �� ��
		userBox->ClearChildren();
		userTable.Reset();

		//�Է°����� ������� ����
		for (const auto& user : users)
			AddUserBox(user);
	}
}