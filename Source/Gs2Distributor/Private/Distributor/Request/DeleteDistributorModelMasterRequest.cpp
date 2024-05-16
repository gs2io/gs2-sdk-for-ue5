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

#include "Distributor/Request/DeleteDistributorModelMasterRequest.h"

namespace Gs2::Distributor::Request
{
    FDeleteDistributorModelMasterRequest::FDeleteDistributorModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        DistributorNameValue(TOptional<FString>())
    {
    }

    FDeleteDistributorModelMasterRequest::FDeleteDistributorModelMasterRequest(
        const FDeleteDistributorModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        DistributorNameValue(From.DistributorNameValue)
    {
    }

    TSharedPtr<FDeleteDistributorModelMasterRequest> FDeleteDistributorModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteDistributorModelMasterRequest> FDeleteDistributorModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteDistributorModelMasterRequest> FDeleteDistributorModelMasterRequest::WithDistributorName(
        const TOptional<FString> DistributorName
    )
    {
        this->DistributorNameValue = DistributorName;
        return SharedThis(this);
    }

    TOptional<FString> FDeleteDistributorModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDeleteDistributorModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDeleteDistributorModelMasterRequest::GetDistributorName() const
    {
        return DistributorNameValue;
    }

    TSharedPtr<FDeleteDistributorModelMasterRequest> FDeleteDistributorModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDeleteDistributorModelMasterRequest>()
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
            ->WithDistributorName(Data->HasField(ANSI_TO_TCHAR("distributorName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("distributorName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDeleteDistributorModelMasterRequest::ToJson() const
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