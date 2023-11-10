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

#include "LoginReward/Request/MarkReceivedByUserIdRequest.h"

namespace Gs2::LoginReward::Request
{
    FMarkReceivedByUserIdRequest::FMarkReceivedByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        BonusModelNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        StepNumberValue(TOptional<int32>())
    {
    }

    FMarkReceivedByUserIdRequest::FMarkReceivedByUserIdRequest(
        const FMarkReceivedByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        BonusModelNameValue(From.BonusModelNameValue),
        UserIdValue(From.UserIdValue),
        StepNumberValue(From.StepNumberValue)
    {
    }

    TSharedPtr<FMarkReceivedByUserIdRequest> FMarkReceivedByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FMarkReceivedByUserIdRequest> FMarkReceivedByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FMarkReceivedByUserIdRequest> FMarkReceivedByUserIdRequest::WithBonusModelName(
        const TOptional<FString> BonusModelName
    )
    {
        this->BonusModelNameValue = BonusModelName;
        return SharedThis(this);
    }

    TSharedPtr<FMarkReceivedByUserIdRequest> FMarkReceivedByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FMarkReceivedByUserIdRequest> FMarkReceivedByUserIdRequest::WithStepNumber(
        const TOptional<int32> StepNumber
    )
    {
        this->StepNumberValue = StepNumber;
        return SharedThis(this);
    }

    TSharedPtr<FMarkReceivedByUserIdRequest> FMarkReceivedByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FMarkReceivedByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FMarkReceivedByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FMarkReceivedByUserIdRequest::GetBonusModelName() const
    {
        return BonusModelNameValue;
    }

    TOptional<FString> FMarkReceivedByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<int32> FMarkReceivedByUserIdRequest::GetStepNumber() const
    {
        return StepNumberValue;
    }

    FString FMarkReceivedByUserIdRequest::GetStepNumberString() const
    {
        if (!StepNumberValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), StepNumberValue.GetValue());
    }

    TOptional<FString> FMarkReceivedByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FMarkReceivedByUserIdRequest> FMarkReceivedByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FMarkReceivedByUserIdRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("namespaceName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithBonusModelName(Data->HasField("bonusModelName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("bonusModelName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("userId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithStepNumber(Data->HasField("stepNumber") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("stepNumber", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FMarkReceivedByUserIdRequest::ToJson() const
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
        if (BonusModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("bonusModelName", BonusModelNameValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (StepNumberValue.IsSet())
        {
            JsonRootObject->SetNumberField("stepNumber", StepNumberValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}