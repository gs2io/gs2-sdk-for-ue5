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

#include "Distributor/Request/UpdateDistributorModelMasterRequest.h"

namespace Gs2::Distributor::Request
{
    FUpdateDistributorModelMasterRequest::FUpdateDistributorModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        DistributorNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        InboxNamespaceIdValue(TOptional<FString>()),
        WhiteListTargetIdsValue(nullptr)
    {
    }

    FUpdateDistributorModelMasterRequest::FUpdateDistributorModelMasterRequest(
        const FUpdateDistributorModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        DistributorNameValue(From.DistributorNameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        InboxNamespaceIdValue(From.InboxNamespaceIdValue),
        WhiteListTargetIdsValue(From.WhiteListTargetIdsValue)
    {
    }

    TSharedPtr<FUpdateDistributorModelMasterRequest> FUpdateDistributorModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateDistributorModelMasterRequest> FUpdateDistributorModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateDistributorModelMasterRequest> FUpdateDistributorModelMasterRequest::WithDistributorName(
        const TOptional<FString> DistributorName
    )
    {
        this->DistributorNameValue = DistributorName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateDistributorModelMasterRequest> FUpdateDistributorModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateDistributorModelMasterRequest> FUpdateDistributorModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateDistributorModelMasterRequest> FUpdateDistributorModelMasterRequest::WithInboxNamespaceId(
        const TOptional<FString> InboxNamespaceId
    )
    {
        this->InboxNamespaceIdValue = InboxNamespaceId;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateDistributorModelMasterRequest> FUpdateDistributorModelMasterRequest::WithWhiteListTargetIds(
        const TSharedPtr<TArray<FString>> WhiteListTargetIds
    )
    {
        this->WhiteListTargetIdsValue = WhiteListTargetIds;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateDistributorModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateDistributorModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateDistributorModelMasterRequest::GetDistributorName() const
    {
        return DistributorNameValue;
    }

    TOptional<FString> FUpdateDistributorModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateDistributorModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<FString> FUpdateDistributorModelMasterRequest::GetInboxNamespaceId() const
    {
        return InboxNamespaceIdValue;
    }

    TSharedPtr<TArray<FString>> FUpdateDistributorModelMasterRequest::GetWhiteListTargetIds() const
    {
        if (!WhiteListTargetIdsValue.IsValid())
        {
            return nullptr;
        }
        return WhiteListTargetIdsValue;
    }

    TSharedPtr<FUpdateDistributorModelMasterRequest> FUpdateDistributorModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateDistributorModelMasterRequest>()
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
              }() : TOptional<FString>())
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("description", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("metadata", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithInboxNamespaceId(Data->HasField("inboxNamespaceId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("inboxNamespaceId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithWhiteListTargetIds(Data->HasField("whiteListTargetIds") ? [Data]() -> TSharedPtr<TArray<FString>>
              {
                  auto v = MakeShared<TArray<FString>>();
                  if (!Data->HasTypedField<EJson::Null>("whiteListTargetIds") && Data->HasTypedField<EJson::Array>("whiteListTargetIds"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("whiteListTargetIds"))
                      {
                          v->Add(JsonObjectValue->AsString());
                      }
                  }
                  return v;
             }() : nullptr);
    }

    TSharedPtr<FJsonObject> FUpdateDistributorModelMasterRequest::ToJson() const
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
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (InboxNamespaceIdValue.IsSet())
        {
            JsonRootObject->SetStringField("inboxNamespaceId", InboxNamespaceIdValue.GetValue());
        }
        if (WhiteListTargetIdsValue != nullptr && WhiteListTargetIdsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *WhiteListTargetIdsValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("whiteListTargetIds", v);
        }
        return JsonRootObject;
    }
}