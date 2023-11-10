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

#include "LoginReward/Request/MarkReceivedRequest.h"

namespace Gs2::LoginReward::Request
{
    FMarkReceivedRequest::FMarkReceivedRequest():
        NamespaceNameValue(TOptional<FString>()),
        BonusModelNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        StepNumberValue(TOptional<int32>())
    {
    }

    FMarkReceivedRequest::FMarkReceivedRequest(
        const FMarkReceivedRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        BonusModelNameValue(From.BonusModelNameValue),
        AccessTokenValue(From.AccessTokenValue),
        StepNumberValue(From.StepNumberValue)
    {
    }

    TSharedPtr<FMarkReceivedRequest> FMarkReceivedRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FMarkReceivedRequest> FMarkReceivedRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FMarkReceivedRequest> FMarkReceivedRequest::WithBonusModelName(
        const TOptional<FString> BonusModelName
    )
    {
        this->BonusModelNameValue = BonusModelName;
        return SharedThis(this);
    }

    TSharedPtr<FMarkReceivedRequest> FMarkReceivedRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FMarkReceivedRequest> FMarkReceivedRequest::WithStepNumber(
        const TOptional<int32> StepNumber
    )
    {
        this->StepNumberValue = StepNumber;
        return SharedThis(this);
    }

    TSharedPtr<FMarkReceivedRequest> FMarkReceivedRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FMarkReceivedRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FMarkReceivedRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FMarkReceivedRequest::GetBonusModelName() const
    {
        return BonusModelNameValue;
    }

    TOptional<FString> FMarkReceivedRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<int32> FMarkReceivedRequest::GetStepNumber() const
    {
        return StepNumberValue;
    }

    FString FMarkReceivedRequest::GetStepNumberString() const
    {
        if (!StepNumberValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), StepNumberValue.GetValue());
    }

    TOptional<FString> FMarkReceivedRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FMarkReceivedRequest> FMarkReceivedRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FMarkReceivedRequest>()
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
            ->WithAccessToken(Data->HasField("xGs2AccessToken") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("xGs2AccessToken", v))
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

    TSharedPtr<FJsonObject> FMarkReceivedRequest::ToJson() const
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
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("xGs2AccessToken", AccessTokenValue.GetValue());
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