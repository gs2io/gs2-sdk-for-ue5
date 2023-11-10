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

#include "Lottery/Request/DescribeProbabilitiesRequest.h"

namespace Gs2::Lottery::Request
{
    FDescribeProbabilitiesRequest::FDescribeProbabilitiesRequest():
        NamespaceNameValue(TOptional<FString>()),
        LotteryNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>())
    {
    }

    FDescribeProbabilitiesRequest::FDescribeProbabilitiesRequest(
        const FDescribeProbabilitiesRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        LotteryNameValue(From.LotteryNameValue),
        AccessTokenValue(From.AccessTokenValue)
    {
    }

    TSharedPtr<FDescribeProbabilitiesRequest> FDescribeProbabilitiesRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeProbabilitiesRequest> FDescribeProbabilitiesRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeProbabilitiesRequest> FDescribeProbabilitiesRequest::WithLotteryName(
        const TOptional<FString> LotteryName
    )
    {
        this->LotteryNameValue = LotteryName;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeProbabilitiesRequest> FDescribeProbabilitiesRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TOptional<FString> FDescribeProbabilitiesRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDescribeProbabilitiesRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDescribeProbabilitiesRequest::GetLotteryName() const
    {
        return LotteryNameValue;
    }

    TOptional<FString> FDescribeProbabilitiesRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TSharedPtr<FDescribeProbabilitiesRequest> FDescribeProbabilitiesRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDescribeProbabilitiesRequest>()
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
            ->WithLotteryName(Data->HasField("lotteryName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("lotteryName", v))
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
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDescribeProbabilitiesRequest::ToJson() const
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
        if (LotteryNameValue.IsSet())
        {
            JsonRootObject->SetStringField("lotteryName", LotteryNameValue.GetValue());
        }
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("xGs2AccessToken", AccessTokenValue.GetValue());
        }
        return JsonRootObject;
    }
}