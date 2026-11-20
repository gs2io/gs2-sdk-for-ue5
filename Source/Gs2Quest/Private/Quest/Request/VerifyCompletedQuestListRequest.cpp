/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include "Quest/Request/VerifyCompletedQuestListRequest.h"

namespace Gs2::Quest::Request
{
    FVerifyCompletedQuestListRequest::FVerifyCompletedQuestListRequest():
        NamespaceNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        QuestGroupNameValue(TOptional<FString>()),
        QuestNameValue(TOptional<FString>()),
        VerifyTypeValue(TOptional<FString>())
    {
    }

    FVerifyCompletedQuestListRequest::FVerifyCompletedQuestListRequest(
        const FVerifyCompletedQuestListRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        AccessTokenValue(From.AccessTokenValue),
        QuestGroupNameValue(From.QuestGroupNameValue),
        QuestNameValue(From.QuestNameValue),
        VerifyTypeValue(From.VerifyTypeValue)
    {
    }

    TSharedPtr<FVerifyCompletedQuestListRequest> FVerifyCompletedQuestListRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyCompletedQuestListRequest> FVerifyCompletedQuestListRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyCompletedQuestListRequest> FVerifyCompletedQuestListRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyCompletedQuestListRequest> FVerifyCompletedQuestListRequest::WithQuestGroupName(
        const TOptional<FString> QuestGroupName
    )
    {
        this->QuestGroupNameValue = QuestGroupName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyCompletedQuestListRequest> FVerifyCompletedQuestListRequest::WithQuestName(
        const TOptional<FString> QuestName
    )
    {
        this->QuestNameValue = QuestName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyCompletedQuestListRequest> FVerifyCompletedQuestListRequest::WithVerifyType(
        const TOptional<FString> VerifyType
    )
    {
        this->VerifyTypeValue = VerifyType;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyCompletedQuestListRequest> FVerifyCompletedQuestListRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FVerifyCompletedQuestListRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FVerifyCompletedQuestListRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FVerifyCompletedQuestListRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<FString> FVerifyCompletedQuestListRequest::GetQuestGroupName() const
    {
        return QuestGroupNameValue;
    }

    TOptional<FString> FVerifyCompletedQuestListRequest::GetQuestName() const
    {
        return QuestNameValue;
    }

    TOptional<FString> FVerifyCompletedQuestListRequest::GetVerifyType() const
    {
        return VerifyTypeValue;
    }

    TOptional<FString> FVerifyCompletedQuestListRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FVerifyCompletedQuestListRequest> FVerifyCompletedQuestListRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVerifyCompletedQuestListRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField(ANSI_TO_TCHAR("namespaceName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceName"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithAccessToken(Data->HasField(ANSI_TO_TCHAR("xGs2AccessToken")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("xGs2AccessToken"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithQuestGroupName(Data->HasField(ANSI_TO_TCHAR("questGroupName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("questGroupName"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithQuestName(Data->HasField(ANSI_TO_TCHAR("questName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("questName"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithVerifyType(Data->HasField(ANSI_TO_TCHAR("verifyType")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("verifyType"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithDuplicationAvoider(Data->HasField(ANSI_TO_TCHAR("duplicationAvoider")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("duplicationAvoider"))) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FVerifyCompletedQuestListRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("contextStack"), ContextStackValue.GetValue());
        }
        if (NamespaceNameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("namespaceName"), NamespaceNameValue.GetValue());
        }
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("xGs2AccessToken"), AccessTokenValue.GetValue());
        }
        if (QuestGroupNameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("questGroupName"), QuestGroupNameValue.GetValue());
        }
        if (QuestNameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("questName"), QuestNameValue.GetValue());
        }
        if (VerifyTypeValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("verifyType"), VerifyTypeValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("duplicationAvoider"), DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}