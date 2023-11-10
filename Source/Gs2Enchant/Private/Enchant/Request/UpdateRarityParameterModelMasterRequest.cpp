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

#include "Enchant/Request/UpdateRarityParameterModelMasterRequest.h"

namespace Gs2::Enchant::Request
{
    FUpdateRarityParameterModelMasterRequest::FUpdateRarityParameterModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        ParameterNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        MaximumParameterCountValue(TOptional<int32>()),
        ParameterCountsValue(nullptr),
        ParametersValue(nullptr)
    {
    }

    FUpdateRarityParameterModelMasterRequest::FUpdateRarityParameterModelMasterRequest(
        const FUpdateRarityParameterModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        ParameterNameValue(From.ParameterNameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        MaximumParameterCountValue(From.MaximumParameterCountValue),
        ParameterCountsValue(From.ParameterCountsValue),
        ParametersValue(From.ParametersValue)
    {
    }

    TSharedPtr<FUpdateRarityParameterModelMasterRequest> FUpdateRarityParameterModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRarityParameterModelMasterRequest> FUpdateRarityParameterModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRarityParameterModelMasterRequest> FUpdateRarityParameterModelMasterRequest::WithParameterName(
        const TOptional<FString> ParameterName
    )
    {
        this->ParameterNameValue = ParameterName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRarityParameterModelMasterRequest> FUpdateRarityParameterModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRarityParameterModelMasterRequest> FUpdateRarityParameterModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRarityParameterModelMasterRequest> FUpdateRarityParameterModelMasterRequest::WithMaximumParameterCount(
        const TOptional<int32> MaximumParameterCount
    )
    {
        this->MaximumParameterCountValue = MaximumParameterCount;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRarityParameterModelMasterRequest> FUpdateRarityParameterModelMasterRequest::WithParameterCounts(
        const TSharedPtr<TArray<TSharedPtr<Model::FRarityParameterCountModel>>> ParameterCounts
    )
    {
        this->ParameterCountsValue = ParameterCounts;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRarityParameterModelMasterRequest> FUpdateRarityParameterModelMasterRequest::WithParameters(
        const TSharedPtr<TArray<TSharedPtr<Model::FRarityParameterValueModel>>> Parameters
    )
    {
        this->ParametersValue = Parameters;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateRarityParameterModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateRarityParameterModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateRarityParameterModelMasterRequest::GetParameterName() const
    {
        return ParameterNameValue;
    }

    TOptional<FString> FUpdateRarityParameterModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateRarityParameterModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<int32> FUpdateRarityParameterModelMasterRequest::GetMaximumParameterCount() const
    {
        return MaximumParameterCountValue;
    }

    FString FUpdateRarityParameterModelMasterRequest::GetMaximumParameterCountString() const
    {
        if (!MaximumParameterCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaximumParameterCountValue.GetValue());
    }

    TSharedPtr<TArray<TSharedPtr<Model::FRarityParameterCountModel>>> FUpdateRarityParameterModelMasterRequest::GetParameterCounts() const
    {
        if (!ParameterCountsValue.IsValid())
        {
            return nullptr;
        }
        return ParameterCountsValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FRarityParameterValueModel>>> FUpdateRarityParameterModelMasterRequest::GetParameters() const
    {
        if (!ParametersValue.IsValid())
        {
            return nullptr;
        }
        return ParametersValue;
    }

    TSharedPtr<FUpdateRarityParameterModelMasterRequest> FUpdateRarityParameterModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateRarityParameterModelMasterRequest>()
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
            ->WithParameterName(Data->HasField("parameterName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("parameterName", v))
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
            ->WithMaximumParameterCount(Data->HasField("maximumParameterCount") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("maximumParameterCount", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
          ->WithParameterCounts(Data->HasField("parameterCounts") ? [Data]() -> TSharedPtr<TArray<Model::FRarityParameterCountModelPtr>>
              {
                  auto v = MakeShared<TArray<Model::FRarityParameterCountModelPtr>>();
                  if (!Data->HasTypedField<EJson::Null>("parameterCounts") && Data->HasTypedField<EJson::Array>("parameterCounts"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("parameterCounts"))
                      {
                          v->Add(Model::FRarityParameterCountModel::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr)
          ->WithParameters(Data->HasField("parameters") ? [Data]() -> TSharedPtr<TArray<Model::FRarityParameterValueModelPtr>>
              {
                  auto v = MakeShared<TArray<Model::FRarityParameterValueModelPtr>>();
                  if (!Data->HasTypedField<EJson::Null>("parameters") && Data->HasTypedField<EJson::Array>("parameters"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("parameters"))
                      {
                          v->Add(Model::FRarityParameterValueModel::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr);
    }

    TSharedPtr<FJsonObject> FUpdateRarityParameterModelMasterRequest::ToJson() const
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
        if (ParameterNameValue.IsSet())
        {
            JsonRootObject->SetStringField("parameterName", ParameterNameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (MaximumParameterCountValue.IsSet())
        {
            JsonRootObject->SetNumberField("maximumParameterCount", MaximumParameterCountValue.GetValue());
        }
        if (ParameterCountsValue != nullptr && ParameterCountsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ParameterCountsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("parameterCounts", v);
        }
        if (ParametersValue != nullptr && ParametersValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ParametersValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("parameters", v);
        }
        return JsonRootObject;
    }
}