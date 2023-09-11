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

#include "SkillTree/Request/UpdateStatusModelMasterRequest.h"

namespace Gs2::SkillTree::Request
{
    FUpdateStatusModelMasterRequest::FUpdateStatusModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        NodeModelNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ReleaseConsumeActionsValue(nullptr),
        RestrainReturnRateValue(TOptional<float>()),
        PremiseNodeNamesValue(nullptr)
    {
    }

    FUpdateStatusModelMasterRequest::FUpdateStatusModelMasterRequest(
        const FUpdateStatusModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        NodeModelNameValue(From.NodeModelNameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        ReleaseConsumeActionsValue(From.ReleaseConsumeActionsValue),
        RestrainReturnRateValue(From.RestrainReturnRateValue),
        PremiseNodeNamesValue(From.PremiseNodeNamesValue)
    {
    }

    TSharedPtr<FUpdateStatusModelMasterRequest> FUpdateStatusModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStatusModelMasterRequest> FUpdateStatusModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStatusModelMasterRequest> FUpdateStatusModelMasterRequest::WithNodeModelName(
        const TOptional<FString> NodeModelName
    )
    {
        this->NodeModelNameValue = NodeModelName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStatusModelMasterRequest> FUpdateStatusModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStatusModelMasterRequest> FUpdateStatusModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStatusModelMasterRequest> FUpdateStatusModelMasterRequest::WithReleaseConsumeActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> ReleaseConsumeActions
    )
    {
        this->ReleaseConsumeActionsValue = ReleaseConsumeActions;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStatusModelMasterRequest> FUpdateStatusModelMasterRequest::WithRestrainReturnRate(
        const TOptional<float> RestrainReturnRate
    )
    {
        this->RestrainReturnRateValue = RestrainReturnRate;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateStatusModelMasterRequest> FUpdateStatusModelMasterRequest::WithPremiseNodeNames(
        const TSharedPtr<TArray<FString>> PremiseNodeNames
    )
    {
        this->PremiseNodeNamesValue = PremiseNodeNames;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateStatusModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateStatusModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateStatusModelMasterRequest::GetNodeModelName() const
    {
        return NodeModelNameValue;
    }

    TOptional<FString> FUpdateStatusModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateStatusModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> FUpdateStatusModelMasterRequest::GetReleaseConsumeActions() const
    {
        if (!ReleaseConsumeActionsValue.IsValid())
        {
            return nullptr;
        }
        return ReleaseConsumeActionsValue;
    }

    TOptional<float> FUpdateStatusModelMasterRequest::GetRestrainReturnRate() const
    {
        return RestrainReturnRateValue;
    }

    FString FUpdateStatusModelMasterRequest::GetRestrainReturnRateString() const
    {
        if (!RestrainReturnRateValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), RestrainReturnRateValue.GetValue());
    }

    TSharedPtr<TArray<FString>> FUpdateStatusModelMasterRequest::GetPremiseNodeNames() const
    {
        if (!PremiseNodeNamesValue.IsValid())
        {
            return nullptr;
        }
        return PremiseNodeNamesValue;
    }

    TSharedPtr<FUpdateStatusModelMasterRequest> FUpdateStatusModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateStatusModelMasterRequest>()
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
            ->WithNodeModelName(Data->HasField("nodeModelName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("nodeModelName", v))
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
          ->WithReleaseConsumeActions(Data->HasField("releaseConsumeActions") ? [Data]() -> TSharedPtr<TArray<Model::FConsumeActionPtr>>
              {
                  auto v = MakeShared<TArray<Model::FConsumeActionPtr>>();
                  if (!Data->HasTypedField<EJson::Null>("releaseConsumeActions") && Data->HasTypedField<EJson::Array>("releaseConsumeActions"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("releaseConsumeActions"))
                      {
                          v->Add(Model::FConsumeAction::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr)
            ->WithRestrainReturnRate(Data->HasField("restrainReturnRate") ? [Data]() -> TOptional<float>
              {
                  float v;
                    if (Data->TryGetNumberField("restrainReturnRate", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<float>();
              }() : TOptional<float>())
          ->WithPremiseNodeNames(Data->HasField("premiseNodeNames") ? [Data]() -> TSharedPtr<TArray<FString>>
              {
                  auto v = MakeShared<TArray<FString>>();
                  if (!Data->HasTypedField<EJson::Null>("premiseNodeNames") && Data->HasTypedField<EJson::Array>("premiseNodeNames"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("premiseNodeNames"))
                      {
                          v->Add(JsonObjectValue->AsString());
                      }
                  }
                  return v;
             }() : nullptr);
    }

    TSharedPtr<FJsonObject> FUpdateStatusModelMasterRequest::ToJson() const
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
        if (NodeModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("nodeModelName", NodeModelNameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (ReleaseConsumeActionsValue != nullptr && ReleaseConsumeActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ReleaseConsumeActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("releaseConsumeActions", v);
        }
        if (RestrainReturnRateValue.IsSet())
        {
            JsonRootObject->SetNumberField("restrainReturnRate", RestrainReturnRateValue.GetValue());
        }
        if (PremiseNodeNamesValue != nullptr && PremiseNodeNamesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *PremiseNodeNamesValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("premiseNodeNames", v);
        }
        return JsonRootObject;
    }
}