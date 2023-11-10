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

#include "Lottery/Request/GetPrizeLimitRequest.h"

namespace Gs2::Lottery::Request
{
    FGetPrizeLimitRequest::FGetPrizeLimitRequest():
        NamespaceNameValue(TOptional<FString>()),
        PrizeTableNameValue(TOptional<FString>()),
        PrizeIdValue(TOptional<FString>())
    {
    }

    FGetPrizeLimitRequest::FGetPrizeLimitRequest(
        const FGetPrizeLimitRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        PrizeTableNameValue(From.PrizeTableNameValue),
        PrizeIdValue(From.PrizeIdValue)
    {
    }

    TSharedPtr<FGetPrizeLimitRequest> FGetPrizeLimitRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetPrizeLimitRequest> FGetPrizeLimitRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetPrizeLimitRequest> FGetPrizeLimitRequest::WithPrizeTableName(
        const TOptional<FString> PrizeTableName
    )
    {
        this->PrizeTableNameValue = PrizeTableName;
        return SharedThis(this);
    }

    TSharedPtr<FGetPrizeLimitRequest> FGetPrizeLimitRequest::WithPrizeId(
        const TOptional<FString> PrizeId
    )
    {
        this->PrizeIdValue = PrizeId;
        return SharedThis(this);
    }

    TOptional<FString> FGetPrizeLimitRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetPrizeLimitRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetPrizeLimitRequest::GetPrizeTableName() const
    {
        return PrizeTableNameValue;
    }

    TOptional<FString> FGetPrizeLimitRequest::GetPrizeId() const
    {
        return PrizeIdValue;
    }

    TSharedPtr<FGetPrizeLimitRequest> FGetPrizeLimitRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetPrizeLimitRequest>()
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
            ->WithPrizeTableName(Data->HasField("prizeTableName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("prizeTableName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithPrizeId(Data->HasField("prizeId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("prizeId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetPrizeLimitRequest::ToJson() const
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
        if (PrizeTableNameValue.IsSet())
        {
            JsonRootObject->SetStringField("prizeTableName", PrizeTableNameValue.GetValue());
        }
        if (PrizeIdValue.IsSet())
        {
            JsonRootObject->SetStringField("prizeId", PrizeIdValue.GetValue());
        }
        return JsonRootObject;
    }
}