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

#include "Exchange/Request/UpdateIncrementalRateModelMasterRequest.h"

namespace Gs2::Exchange::Request
{
    FUpdateIncrementalRateModelMasterRequest::FUpdateIncrementalRateModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        RateNameValue(TOptional<FString>()),
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

    FUpdateIncrementalRateModelMasterRequest::FUpdateIncrementalRateModelMasterRequest(
        const FUpdateIncrementalRateModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        RateNameValue(From.RateNameValue),
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

    TSharedPtr<FUpdateIncrementalRateModelMasterRequest> FUpdateIncrementalRateModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateIncrementalRateModelMasterRequest> FUpdateIncrementalRateModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateIncrementalRateModelMasterRequest> FUpdateIncrementalRateModelMasterRequest::WithRateName(
        const TOptional<FString> RateName
    )
    {
        this->RateNameValue = RateName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateIncrementalRateModelMasterRequest> FUpdateIncrementalRateModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateIncrementalRateModelMasterRequest> FUpdateIncrementalRateModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateIncrementalRateModelMasterRequest> FUpdateIncrementalRateModelMasterRequest::WithConsumeAction(
        const TSharedPtr<Model::FConsumeAction> ConsumeAction
    )
    {
        this->ConsumeActionValue = ConsumeAction;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateIncrementalRateModelMasterRequest> FUpdateIncrementalRateModelMasterRequest::WithCalculateType(
        const TOptional<FString> CalculateType
    )
    {
        this->CalculateTypeValue = CalculateType;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateIncrementalRateModelMasterRequest> FUpdateIncrementalRateModelMasterRequest::WithBaseValue(
        const TOptional<int64> BaseValue
    )
    {
        this->BaseValueValue = BaseValue;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateIncrementalRateModelMasterRequest> FUpdateIncrementalRateModelMasterRequest::WithCoefficientValue(
        const TOptional<int64> CoefficientValue
    )
    {
        this->CoefficientValueValue = CoefficientValue;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateIncrementalRateModelMasterRequest> FUpdateIncrementalRateModelMasterRequest::WithCalculateScriptId(
        const TOptional<FString> CalculateScriptId
    )
    {
        this->CalculateScriptIdValue = CalculateScriptId;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateIncrementalRateModelMasterRequest> FUpdateIncrementalRateModelMasterRequest::WithExchangeCountId(
        const TOptional<FString> ExchangeCountId
    )
    {
        this->ExchangeCountIdValue = ExchangeCountId;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateIncrementalRateModelMasterRequest> FUpdateIncrementalRateModelMasterRequest::WithMaximumExchangeCount(
        const TOptional<int32> MaximumExchangeCount
    )
    {
        this->MaximumExchangeCountValue = MaximumExchangeCount;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateIncrementalRateModelMasterRequest> FUpdateIncrementalRateModelMasterRequest::WithAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> AcquireActions
    )
    {
        this->AcquireActionsValue = AcquireActions;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateIncrementalRateModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateIncrementalRateModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateIncrementalRateModelMasterRequest::GetRateName() const
    {
        return RateNameValue;
    }

    TOptional<FString> FUpdateIncrementalRateModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateIncrementalRateModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TSharedPtr<Model::FConsumeAction> FUpdateIncrementalRateModelMasterRequest::GetConsumeAction() const
    {
        if (!ConsumeActionValue.IsValid())
        {
            return nullptr;
        }
        return ConsumeActionValue;
    }

    TOptional<FString> FUpdateIncrementalRateModelMasterRequest::GetCalculateType() const
    {
        return CalculateTypeValue;
    }

    TOptional<int64> FUpdateIncrementalRateModelMasterRequest::GetBaseValue() const
    {
        return BaseValueValue;
    }

    FString FUpdateIncrementalRateModelMasterRequest::GetBaseValueString() const
    {
        if (!BaseValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), BaseValueValue.GetValue());
    }

    TOptional<int64> FUpdateIncrementalRateModelMasterRequest::GetCoefficientValue() const
    {
        return CoefficientValueValue;
    }

    FString FUpdateIncrementalRateModelMasterRequest::GetCoefficientValueString() const
    {
        if (!CoefficientValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CoefficientValueValue.GetValue());
    }

    TOptional<FString> FUpdateIncrementalRateModelMasterRequest::GetCalculateScriptId() const
    {
        return CalculateScriptIdValue;
    }

    TOptional<FString> FUpdateIncrementalRateModelMasterRequest::GetExchangeCountId() const
    {
        return ExchangeCountIdValue;
    }

    TOptional<int32> FUpdateIncrementalRateModelMasterRequest::GetMaximumExchangeCount() const
    {
        return MaximumExchangeCountValue;
    }

    FString FUpdateIncrementalRateModelMasterRequest::GetMaximumExchangeCountString() const
    {
        if (!MaximumExchangeCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaximumExchangeCountValue.GetValue());
    }

    TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FUpdateIncrementalRateModelMasterRequest::GetAcquireActions() const
    {
        if (!AcquireActionsValue.IsValid())
        {
            return nullptr;
        }
        return AcquireActionsValue;
    }

    TSharedPtr<FUpdateIncrementalRateModelMasterRequest> FUpdateIncrementalRateModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateIncrementalRateModelMasterRequest>()
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
            ->WithRateName(Data->HasField("rateName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("rateName", v))
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
                  FString v;
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
                  FString v;
                    if (Data->TryGetStringField("calculateScriptId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithExchangeCountId(Data->HasField("exchangeCountId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
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

    TSharedPtr<FJsonObject> FUpdateIncrementalRateModelMasterRequest::ToJson() const
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
        if (RateNameValue.IsSet())
        {
            JsonRootObject->SetStringField("rateName", RateNameValue.GetValue());
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