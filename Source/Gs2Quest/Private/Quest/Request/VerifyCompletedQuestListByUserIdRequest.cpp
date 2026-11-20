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

#include "Quest/Request/VerifyCompletedQuestListByUserIdRequest.h"

namespace Gs2::Quest::Request
{
    FVerifyCompletedQuestListByUserIdRequest::FVerifyCompletedQuestListByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        QuestGroupNameValue(TOptional<FString>()),
        QuestNameValue(TOptional<FString>()),
        VerifyTypeValue(TOptional<FString>()),
        TimeOffsetTokenValue(TOptional<FString>())
    {
    }

    FVerifyCompletedQuestListByUserIdRequest::FVerifyCompletedQuestListByUserIdRequest(
        const FVerifyCompletedQuestListByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        QuestGroupNameValue(From.QuestGroupNameValue),
        QuestNameValue(From.QuestNameValue),
        VerifyTypeValue(From.VerifyTypeValue),
        TimeOffsetTokenValue(From.TimeOffsetTokenValue)
    {
    }

    TSharedPtr<FVerifyCompletedQuestListByUserIdRequest> FVerifyCompletedQuestListByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyCompletedQuestListByUserIdRequest> FVerifyCompletedQuestListByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyCompletedQuestListByUserIdRequest> FVerifyCompletedQuestListByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyCompletedQuestListByUserIdRequest> FVerifyCompletedQuestListByUserIdRequest::WithQuestGroupName(
        const TOptional<FString> QuestGroupName
    )
    {
        this->QuestGroupNameValue = QuestGroupName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyCompletedQuestListByUserIdRequest> FVerifyCompletedQuestListByUserIdRequest::WithQuestName(
        const TOptional<FString> QuestName
    )
    {
        this->QuestNameValue = QuestName;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyCompletedQuestListByUserIdRequest> FVerifyCompletedQuestListByUserIdRequest::WithVerifyType(
        const TOptional<FString> VerifyType
    )
    {
        this->VerifyTypeValue = VerifyType;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyCompletedQuestListByUserIdRequest> FVerifyCompletedQuestListByUserIdRequest::WithTimeOffsetToken(
        const TOptional<FString> TimeOffsetToken
    )
    {
        this->TimeOffsetTokenValue = TimeOffsetToken;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyCompletedQuestListByUserIdRequest> FVerifyCompletedQuestListByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FVerifyCompletedQuestListByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FVerifyCompletedQuestListByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FVerifyCompletedQuestListByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FVerifyCompletedQuestListByUserIdRequest::GetQuestGroupName() const
    {
        return QuestGroupNameValue;
    }

    TOptional<FString> FVerifyCompletedQuestListByUserIdRequest::GetQuestName() const
    {
        return QuestNameValue;
    }

    TOptional<FString> FVerifyCompletedQuestListByUserIdRequest::GetVerifyType() const
    {
        return VerifyTypeValue;
    }

    TOptional<FString> FVerifyCompletedQuestListByUserIdRequest::GetTimeOffsetToken() const
    {
        return TimeOffsetTokenValue;
    }

    TOptional<FString> FVerifyCompletedQuestListByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FVerifyCompletedQuestListByUserIdRequest> FVerifyCompletedQuestListByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVerifyCompletedQuestListByUserIdRequest>()
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
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
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
            ->WithTimeOffsetToken(Data->HasField(ANSI_TO_TCHAR("timeOffsetToken")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("timeOffsetToken"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithDuplicationAvoider(Data->HasField(ANSI_TO_TCHAR("duplicationAvoider")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("duplicationAvoider"))) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FVerifyCompletedQuestListByUserIdRequest::ToJson() const
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
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("userId"), UserIdValue.GetValue());
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
        if (TimeOffsetTokenValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("timeOffsetToken"), TimeOffsetTokenValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("duplicationAvoider"), DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}