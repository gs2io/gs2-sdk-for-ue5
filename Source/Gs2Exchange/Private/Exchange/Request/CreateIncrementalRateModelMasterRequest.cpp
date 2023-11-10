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

#include "Exchange/Request/CreateIncrementalRateModelMasterRequest.h"

namespace Gs2::Exchange::Request
{
    FCreateIncrementalRateModelMasterRequest::FCreateIncrementalRateModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ConsumeActionValue(nullptr),
        CalculateTypeValue(TOptional<FString>()),
        BaseValueValue(TOptional<int64>()),
        CoefficientValueValue(TOptional<int64>()),
        CalculateScriptIdValue(TOptional<FString>()),
        ExchangeCountIdValue(TOptional<FString>()),
        MaximumExchangeCountValue(TOptional<int32>()),
        AcquireActionsValue(nullptr)
    {
    }

    FCreateIncrementalRateModelMasterRequest::FCreateIncrementalRateModelMasterRequest(
        const FCreateIncrementalRateModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        ConsumeActionValue(From.ConsumeActionValue),
        CalculateTypeValue(From.CalculateTypeValue),
        BaseValueValue(From.BaseValueValue),
        CoefficientValueValue(From.CoefficientValueValue),
        CalculateScriptIdValue(From.CalculateScriptIdValue),
        ExchangeCountIdValue(From.ExchangeCountIdValue),
        MaximumExchangeCountValue(From.MaximumExchangeCountValue),
        AcquireActionsValue(From.AcquireActionsValue)
    {
    }

    TSharedPtr<FCreateIncrementalRateModelMasterRequest> FCreateIncrementalRateModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCreateIncrementalRateModelMasterRequest> FCreateIncrementalRateModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FCreateIncrementalRateModelMasterRequest> FCreateIncrementalRateModelMasterRequest::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FCreateIncrementalRateModelMasterRequest> FCreateIncrementalRateModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FCreateIncrementalRateModelMasterRequest> FCreateIncrementalRateModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FCreateIncrementalRateModelMasterRequest> FCreateIncrementalRateModelMasterRequest::WithConsumeAction(
        const TSharedPtr<Model::FConsumeAction> ConsumeAction
    )
    {
        this->ConsumeActionValue = ConsumeAction;
        return SharedThis(this);
    }

    TSharedPtr<FCreateIncrementalRateModelMasterRequest> FCreateIncrementalRateModelMasterRequest::WithCalculateType(
        const TOptional<FString> CalculateType
    )
    {
        this->CalculateTypeValue = CalculateType;
        return SharedThis(this);
    }

    TSharedPtr<FCreateIncrementalRateModelMasterRequest> FCreateIncrementalRateModelMasterRequest::WithBaseValue(
        const TOptional<int64> BaseValue
    )
    {
        this->BaseValueValue = BaseValue;
        return SharedThis(this);
    }

    TSharedPtr<FCreateIncrementalRateModelMasterRequest> FCreateIncrementalRateModelMasterRequest::WithCoefficientValue(
        const TOptional<int64> CoefficientValue
    )
    {
        this->CoefficientValueValue = CoefficientValue;
        return SharedThis(this);
    }

    TSharedPtr<FCreateIncrementalRateModelMasterRequest> FCreateIncrementalRateModelMasterRequest::WithCalculateScriptId(
        const TOptional<FString> CalculateScriptId
    )
    {
        this->CalculateScriptIdValue = CalculateScriptId;
        return SharedThis(this);
    }

    TSharedPtr<FCreateIncrementalRateModelMasterRequest> FCreateIncrementalRateModelMasterRequest::WithExchangeCountId(
        const TOptional<FString> ExchangeCountId
    )
    {
        this->ExchangeCountIdValue = ExchangeCountId;
        return SharedThis(this);
    }

    TSharedPtr<FCreateIncrementalRateModelMasterRequest> FCreateIncrementalRateModelMasterRequest::WithMaximumExchangeCount(
        const TOptional<int32> MaximumExchangeCount
    )
    {
        this->MaximumExchangeCountValue = MaximumExchangeCount;
        return SharedThis(this);
    }

    TSharedPtr<FCreateIncrementalRateModelMasterRequest> FCreateIncrementalRateModelMasterRequest::WithAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> AcquireActions
    )
    {
        this->AcquireActionsValue = AcquireActions;
        return SharedThis(this);
    }

    TOptional<FString> FCreateIncrementalRateModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCreateIncrementalRateModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FCreateIncrementalRateModelMasterRequest::GetName() const
    {
        return NameValue;
    }

    TOptional<FString> FCreateIncrementalRateModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FCreateIncrementalRateModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TSharedPtr<Model::FConsumeAction> FCreateIncrementalRateModelMasterRequest::GetConsumeAction() const
    {
        if (!ConsumeActionValue.IsValid())
        {
            return nullptr;
        }
        return ConsumeActionValue;
    }

    TOptional<FString> FCreateIncrementalRateModelMasterRequest::GetCalculateType() const
    {
        return CalculateTypeValue;
    }

    TOptional<int64> FCreateIncrementalRateModelMasterRequest::GetBaseValue() const
    {
        return BaseValueValue;
    }

    FString FCreateIncrementalRateModelMasterRequest::GetBaseValueString() const
    {
        if (!BaseValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), BaseValueValue.GetValue());
    }

    TOptional<int64> FCreateIncrementalRateModelMasterRequest::GetCoefficientValue() const
    {
        return CoefficientValueValue;
    }

    FString FCreateIncrementalRateModelMasterRequest::GetCoefficientValueString() const
    {
        if (!CoefficientValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CoefficientValueValue.GetValue());
    }

    TOptional<FString> FCreateIncrementalRateModelMasterRequest::GetCalculateScriptId() const
    {
        return CalculateScriptIdValue;
    }

    TOptional<FString> FCreateIncrementalRateModelMasterRequest::GetExchangeCountId() const
    {
        return ExchangeCountIdValue;
    }

    TOptional<int32> FCreateIncrementalRateModelMasterRequest::GetMaximumExchangeCount() const
    {
        return MaximumExchangeCountValue;
    }

    FString FCreateIncrementalRateModelMasterRequest::GetMaximumExchangeCountString() const
    {
        if (!MaximumExchangeCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaximumExchangeCountValue.GetValue());
    }

    TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FCreateIncrementalRateModelMasterRequest::GetAcquireActions() const
    {
        if (!AcquireActionsValue.IsValid())
        {
            return nullptr;
        }
        return AcquireActionsValue;
    }

    TSharedPtr<FCreateIncrementalRateModelMasterRequest> FCreateIncrementalRateModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateIncrementalRateModelMasterRequest>()
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
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("name", v))
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
          ->WithConsumeAction(Data->HasField("consumeAction") ? [Data]() -> Model::FConsumeActionPtr
              {
                  if (Data->HasTypedField<EJson::Null>("consumeAction"))
                  {
                      return nullptr;
                  }
                  return Model::FConsumeAction::FromJson(Data->GetObjectField("consumeAction"));
             }() : nullptr)
            ->WithCalculateType(Data->HasField("calculateType") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("calculateType", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithBaseValue(Data->HasField("baseValue") ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField("baseValue", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
            ->WithCoefficientValue(Data->HasField("coefficientValue") ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField("coefficientValue", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
            ->WithCalculateScriptId(Data->HasField("calculateScriptId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("calculateScriptId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithExchangeCountId(Data->HasField("exchangeCountId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("exchangeCountId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMaximumExchangeCount(Data->HasField("maximumExchangeCount") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("maximumExchangeCount", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
          ->WithAcquireActions(Data->HasField("acquireActions") ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionPtr>>
              {
                  auto v = MakeShared<TArray<Model::FAcquireActionPtr>>();
                  if (!Data->HasTypedField<EJson::Null>("acquireActions") && Data->HasTypedField<EJson::Array>("acquireActions"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("acquireActions"))
                      {
                          v->Add(Model::FAcquireAction::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr);
    }

    TSharedPtr<FJsonObject> FCreateIncrementalRateModelMasterRequest::ToJson() const
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
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (ConsumeActionValue != nullptr && ConsumeActionValue.IsValid())
        {
            JsonRootObject->SetObjectField("consumeAction", ConsumeActionValue->ToJson());
        }
        if (CalculateTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("calculateType", CalculateTypeValue.GetValue());
        }
        if (BaseValueValue.IsSet())
        {
            JsonRootObject->SetStringField("baseValue", FString::Printf(TEXT("%lld"), BaseValueValue.GetValue()));
        }
        if (CoefficientValueValue.IsSet())
        {
            JsonRootObject->SetStringField("coefficientValue", FString::Printf(TEXT("%lld"), CoefficientValueValue.GetValue()));
        }
        if (CalculateScriptIdValue.IsSet())
        {
            JsonRootObject->SetStringField("calculateScriptId", CalculateScriptIdValue.GetValue());
        }
        if (ExchangeCountIdValue.IsSet())
        {
            JsonRootObject->SetStringField("exchangeCountId", ExchangeCountIdValue.GetValue());
        }
        if (MaximumExchangeCountValue.IsSet())
        {
            JsonRootObject->SetNumberField("maximumExchangeCount", MaximumExchangeCountValue.GetValue());
        }
        if (AcquireActionsValue != nullptr && AcquireActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *AcquireActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("acquireActions", v);
        }
        return JsonRootObject;
    }
}