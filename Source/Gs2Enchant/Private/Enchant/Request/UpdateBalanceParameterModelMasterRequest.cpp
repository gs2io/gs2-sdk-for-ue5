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

#include "Enchant/Request/UpdateBalanceParameterModelMasterRequest.h"

namespace Gs2::Enchant::Request
{
    FUpdateBalanceParameterModelMasterRequest::FUpdateBalanceParameterModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        ParameterNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        TotalValueValue(TOptional<int64>()),
        InitialValueStrategyValue(TOptional<FString>()),
        ParametersValue(nullptr)
    {
    }

    FUpdateBalanceParameterModelMasterRequest::FUpdateBalanceParameterModelMasterRequest(
        const FUpdateBalanceParameterModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        ParameterNameValue(From.ParameterNameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        TotalValueValue(From.TotalValueValue),
        InitialValueStrategyValue(From.InitialValueStrategyValue),
        ParametersValue(From.ParametersValue)
    {
    }

    TSharedPtr<FUpdateBalanceParameterModelMasterRequest> FUpdateBalanceParameterModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateBalanceParameterModelMasterRequest> FUpdateBalanceParameterModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateBalanceParameterModelMasterRequest> FUpdateBalanceParameterModelMasterRequest::WithParameterName(
        const TOptional<FString> ParameterName
    )
    {
        this->ParameterNameValue = ParameterName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateBalanceParameterModelMasterRequest> FUpdateBalanceParameterModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateBalanceParameterModelMasterRequest> FUpdateBalanceParameterModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateBalanceParameterModelMasterRequest> FUpdateBalanceParameterModelMasterRequest::WithTotalValue(
        const TOptional<int64> TotalValue
    )
    {
        this->TotalValueValue = TotalValue;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateBalanceParameterModelMasterRequest> FUpdateBalanceParameterModelMasterRequest::WithInitialValueStrategy(
        const TOptional<FString> InitialValueStrategy
    )
    {
        this->InitialValueStrategyValue = InitialValueStrategy;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateBalanceParameterModelMasterRequest> FUpdateBalanceParameterModelMasterRequest::WithParameters(
        const TSharedPtr<TArray<TSharedPtr<Model::FBalanceParameterValueModel>>> Parameters
    )
    {
        this->ParametersValue = Parameters;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateBalanceParameterModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateBalanceParameterModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateBalanceParameterModelMasterRequest::GetParameterName() const
    {
        return ParameterNameValue;
    }

    TOptional<FString> FUpdateBalanceParameterModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateBalanceParameterModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<int64> FUpdateBalanceParameterModelMasterRequest::GetTotalValue() const
    {
        return TotalValueValue;
    }

    FString FUpdateBalanceParameterModelMasterRequest::GetTotalValueString() const
    {
        if (!TotalValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TotalValueValue.GetValue());
    }

    TOptional<FString> FUpdateBalanceParameterModelMasterRequest::GetInitialValueStrategy() const
    {
        return InitialValueStrategyValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FBalanceParameterValueModel>>> FUpdateBalanceParameterModelMasterRequest::GetParameters() const
    {
        if (!ParametersValue.IsValid())
        {
            return nullptr;
        }
        return ParametersValue;
    }

    TSharedPtr<FUpdateBalanceParameterModelMasterRequest> FUpdateBalanceParameterModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateBalanceParameterModelMasterRequest>()
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
            ->WithParameterName(Data->HasField("parameterName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("parameterName", v))
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
            ->WithTotalValue(Data->HasField("totalValue") ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField("totalValue", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
            ->WithInitialValueStrategy(Data->HasField("initialValueStrategy") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("initialValueStrategy", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithParameters(Data->HasField("parameters") ? [Data]() -> TSharedPtr<TArray<Model::FBalanceParameterValueModelPtr>>
              {
                  auto v = MakeShared<TArray<Model::FBalanceParameterValueModelPtr>>();
                  if (!Data->HasTypedField<EJson::Null>("parameters") && Data->HasTypedField<EJson::Array>("parameters"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("parameters"))
                      {
                          v->Add(Model::FBalanceParameterValueModel::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr);
    }

    TSharedPtr<FJsonObject> FUpdateBalanceParameterModelMasterRequest::ToJson() const
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
        if (TotalValueValue.IsSet())
        {
            JsonRootObject->SetStringField("totalValue", FString::Printf(TEXT("%lld"), TotalValueValue.GetValue()));
        }
        if (InitialValueStrategyValue.IsSet())
        {
            JsonRootObject->SetStringField("initialValueStrategy", InitialValueStrategyValue.GetValue());
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