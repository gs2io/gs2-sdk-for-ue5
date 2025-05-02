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

#include "Account/Request/UpdateDataOwnerByUserIdRequest.h"

namespace Gs2::Account::Request
{
    FUpdateDataOwnerByUserIdRequest::FUpdateDataOwnerByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        DataOwnerNameValue(TOptional<FString>()),
        TimeOffsetTokenValue(TOptional<FString>())
    {
    }

    FUpdateDataOwnerByUserIdRequest::FUpdateDataOwnerByUserIdRequest(
        const FUpdateDataOwnerByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        DataOwnerNameValue(From.DataOwnerNameValue),
        TimeOffsetTokenValue(From.TimeOffsetTokenValue)
    {
    }

    TSharedPtr<FUpdateDataOwnerByUserIdRequest> FUpdateDataOwnerByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateDataOwnerByUserIdRequest> FUpdateDataOwnerByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateDataOwnerByUserIdRequest> FUpdateDataOwnerByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateDataOwnerByUserIdRequest> FUpdateDataOwnerByUserIdRequest::WithDataOwnerName(
        const TOptional<FString> DataOwnerName
    )
    {
        this->DataOwnerNameValue = DataOwnerName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateDataOwnerByUserIdRequest> FUpdateDataOwnerByUserIdRequest::WithTimeOffsetToken(
        const TOptional<FString> TimeOffsetToken
    )
    {
        this->TimeOffsetTokenValue = TimeOffsetToken;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateDataOwnerByUserIdRequest> FUpdateDataOwnerByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateDataOwnerByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateDataOwnerByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateDataOwnerByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FUpdateDataOwnerByUserIdRequest::GetDataOwnerName() const
    {
        return DataOwnerNameValue;
    }

    TOptional<FString> FUpdateDataOwnerByUserIdRequest::GetTimeOffsetToken() const
    {
        return TimeOffsetTokenValue;
    }

    TOptional<FString> FUpdateDataOwnerByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FUpdateDataOwnerByUserIdRequest> FUpdateDataOwnerByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateDataOwnerByUserIdRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField(ANSI_TO_TCHAR("namespaceName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDataOwnerName(Data->HasField(ANSI_TO_TCHAR("dataOwnerName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("dataOwnerName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithTimeOffsetToken(Data->HasField(ANSI_TO_TCHAR("timeOffsetToken")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("timeOffsetToken"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithDuplicationAvoider(Data->HasField(ANSI_TO_TCHAR("duplicationAvoider")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("duplicationAvoider"))) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FUpdateDataOwnerByUserIdRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (NamespaceNameValue.IsSet())
        {
            JsonRootObject->SetStringField("namespaceName", NamespaceNameValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (DataOwnerNameValue.IsSet())
        {
            JsonRootObject->SetStringField("dataOwnerName", DataOwnerNameValue.GetValue());
        }
        if (TimeOffsetTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("timeOffsetToken", TimeOffsetTokenValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}