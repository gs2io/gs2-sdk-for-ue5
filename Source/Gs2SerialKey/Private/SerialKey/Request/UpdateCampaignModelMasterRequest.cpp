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

#include "SerialKey/Request/UpdateCampaignModelMasterRequest.h"

namespace Gs2::SerialKey::Request
{
    FUpdateCampaignModelMasterRequest::FUpdateCampaignModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        CampaignModelNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        EnableCampaignCodeValue(TOptional<bool>())
    {
    }

    FUpdateCampaignModelMasterRequest::FUpdateCampaignModelMasterRequest(
        const FUpdateCampaignModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        CampaignModelNameValue(From.CampaignModelNameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        EnableCampaignCodeValue(From.EnableCampaignCodeValue)
    {
    }

    TSharedPtr<FUpdateCampaignModelMasterRequest> FUpdateCampaignModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCampaignModelMasterRequest> FUpdateCampaignModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCampaignModelMasterRequest> FUpdateCampaignModelMasterRequest::WithCampaignModelName(
        const TOptional<FString> CampaignModelName
    )
    {
        this->CampaignModelNameValue = CampaignModelName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCampaignModelMasterRequest> FUpdateCampaignModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCampaignModelMasterRequest> FUpdateCampaignModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCampaignModelMasterRequest> FUpdateCampaignModelMasterRequest::WithEnableCampaignCode(
        const TOptional<bool> EnableCampaignCode
    )
    {
        this->EnableCampaignCodeValue = EnableCampaignCode;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateCampaignModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateCampaignModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateCampaignModelMasterRequest::GetCampaignModelName() const
    {
        return CampaignModelNameValue;
    }

    TOptional<FString> FUpdateCampaignModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateCampaignModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<bool> FUpdateCampaignModelMasterRequest::GetEnableCampaignCode() const
    {
        return EnableCampaignCodeValue;
    }

    FString FUpdateCampaignModelMasterRequest::GetEnableCampaignCodeString() const
    {
        if (!EnableCampaignCodeValue.IsSet())
        {
            return FString("null");
        }
        return FString(EnableCampaignCodeValue.GetValue() ? "true" : "false");
    }

    TSharedPtr<FUpdateCampaignModelMasterRequest> FUpdateCampaignModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateCampaignModelMasterRequest>()
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
            ->WithCampaignModelName(Data->HasField("campaignModelName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("campaignModelName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("description", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("metadata", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithEnableCampaignCode(Data->HasField("enableCampaignCode") ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField("enableCampaignCode", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>());
    }

    TSharedPtr<FJsonObject> FUpdateCampaignModelMasterRequest::ToJson() const
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
        if (CampaignModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("campaignModelName", CampaignModelNameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (EnableCampaignCodeValue.IsSet())
        {
            JsonRootObject->SetBoolField("enableCampaignCode", EnableCampaignCodeValue.GetValue());
        }
        return JsonRootObject;
    }
}