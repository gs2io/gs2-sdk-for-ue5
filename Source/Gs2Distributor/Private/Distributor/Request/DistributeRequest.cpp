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

#include "Distributor/Request/DistributeRequest.h"

namespace Gs2::Distributor::Request
{
    FDistributeRequest::FDistributeRequest():
        NamespaceNameValue(TOptional<FString>()),
        DistributorNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        DistributeResourceValue(nullptr)
    {
    }

    FDistributeRequest::FDistributeRequest(
        const FDistributeRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        DistributorNameValue(From.DistributorNameValue),
        UserIdValue(From.UserIdValue),
        DistributeResourceValue(From.DistributeResourceValue)
    {
    }

    TSharedPtr<FDistributeRequest> FDistributeRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDistributeRequest> FDistributeRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDistributeRequest> FDistributeRequest::WithDistributorName(
        const TOptional<FString> DistributorName
    )
    {
        this->DistributorNameValue = DistributorName;
        return SharedThis(this);
    }

    TSharedPtr<FDistributeRequest> FDistributeRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FDistributeRequest> FDistributeRequest::WithDistributeResource(
        const TSharedPtr<Model::FDistributeResource> DistributeResource
    )
    {
        this->DistributeResourceValue = DistributeResource;
        return SharedThis(this);
    }

    TOptional<FString> FDistributeRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDistributeRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDistributeRequest::GetDistributorName() const
    {
        return DistributorNameValue;
    }

    TOptional<FString> FDistributeRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TSharedPtr<Model::FDistributeResource> FDistributeRequest::GetDistributeResource() const
    {
        if (!DistributeResourceValue.IsValid())
        {
            return nullptr;
        }
        return DistributeResourceValue;
    }

    TSharedPtr<FDistributeRequest> FDistributeRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDistributeRequest>()
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
            ->WithDistributorName(Data->HasField("distributorName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("distributorName", v))
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
          ->WithDistributeResource(Data->HasField("distributeResource") ? [Data]() -> Model::FDistributeResourcePtr
              {
                  if (Data->HasTypedField<EJson::Null>("distributeResource"))
                  {
                      return nullptr;
                  }
                  return Model::FDistributeResource::FromJson(Data->GetObjectField("distributeResource"));
              }() : nullptr);
    }

    TSharedPtr<FJsonObject> FDistributeRequest::ToJson() const
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
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (DistributeResourceValue != nullptr && DistributeResourceValue.IsValid())
        {
            JsonRootObject->SetObjectField("distributeResource", DistributeResourceValue->ToJson());
        }
        return JsonRootObject;
    }
}