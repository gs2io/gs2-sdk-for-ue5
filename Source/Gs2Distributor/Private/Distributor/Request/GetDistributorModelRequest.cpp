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

#include "Distributor/Request/GetDistributorModelRequest.h"

namespace Gs2::Distributor::Request
{
    FGetDistributorModelRequest::FGetDistributorModelRequest():
        NamespaceNameValue(TOptional<FString>()),
        DistributorNameValue(TOptional<FString>())
    {
    }

    FGetDistributorModelRequest::FGetDistributorModelRequest(
        const FGetDistributorModelRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        DistributorNameValue(From.DistributorNameValue)
    {
    }

    TSharedPtr<FGetDistributorModelRequest> FGetDistributorModelRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetDistributorModelRequest> FGetDistributorModelRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetDistributorModelRequest> FGetDistributorModelRequest::WithDistributorName(
        const TOptional<FString> DistributorName
    )
    {
        this->DistributorNameValue = DistributorName;
        return SharedThis(this);
    }

    TOptional<FString> FGetDistributorModelRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetDistributorModelRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetDistributorModelRequest::GetDistributorName() const
    {
        return DistributorNameValue;
    }

    TSharedPtr<FGetDistributorModelRequest> FGetDistributorModelRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetDistributorModelRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("namespaceName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDistributorName(Data->HasField("distributorName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("distributorName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetDistributorModelRequest::ToJson() const
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
        if (DistributorNameValue.IsSet())
        {
            JsonRootObject->SetStringField("distributorName", DistributorNameValue.GetValue());
        }
        return JsonRootObject;
    }
}