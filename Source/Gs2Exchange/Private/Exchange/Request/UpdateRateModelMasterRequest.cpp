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

#include "Exchange/Request/UpdateRateModelMasterRequest.h"

namespace Gs2::Exchange::Request
{
    FUpdateRateModelMasterRequest::FUpdateRateModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        RateNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        TimingTypeValue(TOptional<FString>()),
        LockTimeValue(TOptional<int32>()),
        AcquireActionsValue(nullptr),
        VerifyActionsValue(nullptr),
        ConsumeActionsValue(nullptr)
    {
    }

    FUpdateRateModelMasterRequest::FUpdateRateModelMasterRequest(
        const FUpdateRateModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        RateNameValue(From.RateNameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        TimingTypeValue(From.TimingTypeValue),
        LockTimeValue(From.LockTimeValue),
        AcquireActionsValue(From.AcquireActionsValue),
        VerifyActionsValue(From.VerifyActionsValue),
        ConsumeActionsValue(From.ConsumeActionsValue)
    {
    }

    TSharedPtr<FUpdateRateModelMasterRequest> FUpdateRateModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRateModelMasterRequest> FUpdateRateModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRateModelMasterRequest> FUpdateRateModelMasterRequest::WithRateName(
        const TOptional<FString> RateName
    )
    {
        this->RateNameValue = RateName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRateModelMasterRequest> FUpdateRateModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRateModelMasterRequest> FUpdateRateModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRateModelMasterRequest> FUpdateRateModelMasterRequest::WithTimingType(
        const TOptional<FString> TimingType
    )
    {
        this->TimingTypeValue = TimingType;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRateModelMasterRequest> FUpdateRateModelMasterRequest::WithLockTime(
        const TOptional<int32> LockTime
    )
    {
        this->LockTimeValue = LockTime;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRateModelMasterRequest> FUpdateRateModelMasterRequest::WithAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> AcquireActions
    )
    {
        this->AcquireActionsValue = AcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRateModelMasterRequest> FUpdateRateModelMasterRequest::WithVerifyActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> VerifyActions
    )
    {
        this->VerifyActionsValue = VerifyActions;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRateModelMasterRequest> FUpdateRateModelMasterRequest::WithConsumeActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> ConsumeActions
    )
    {
        this->ConsumeActionsValue = ConsumeActions;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateRateModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateRateModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateRateModelMasterRequest::GetRateName() const
    {
        return RateNameValue;
    }

    TOptional<FString> FUpdateRateModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateRateModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<FString> FUpdateRateModelMasterRequest::GetTimingType() const
    {
        return TimingTypeValue;
    }

    TOptional<int32> FUpdateRateModelMasterRequest::GetLockTime() const
    {
        return LockTimeValue;
    }

    FString FUpdateRateModelMasterRequest::GetLockTimeString() const
    {
        if (!LockTimeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), LockTimeValue.GetValue());
    }

    TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FUpdateRateModelMasterRequest::GetAcquireActions() const
    {
        if (!AcquireActionsValue.IsValid())
        {
            return nullptr;
        }
        return AcquireActionsValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> FUpdateRateModelMasterRequest::GetVerifyActions() const
    {
        if (!VerifyActionsValue.IsValid())
        {
            return nullptr;
        }
        return VerifyActionsValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> FUpdateRateModelMasterRequest::GetConsumeActions() const
    {
        if (!ConsumeActionsValue.IsValid())
        {
            return nullptr;
        }
        return ConsumeActionsValue;
    }

    TSharedPtr<FUpdateRateModelMasterRequest> FUpdateRateModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateRateModelMasterRequest>()
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
            ->WithRateName(Data->HasField(ANSI_TO_TCHAR("rateName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("rateName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDescription(Data->HasField(ANSI_TO_TCHAR("description")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("description"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMetadata(Data->HasField(ANSI_TO_TCHAR("metadata")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("metadata"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithTimingType(Data->HasField(ANSI_TO_TCHAR("timingType")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("timingType"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithLockTime(Data->HasField(ANSI_TO_TCHAR("lockTime")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("lockTime"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
          ->WithAcquireActions(Data->HasField(ANSI_TO_TCHAR("acquireActions")) ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionPtr>>
              {
                  auto v = MakeShared<TArray<Model::FAcquireActionPtr>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("acquireActions")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("acquireActions")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("acquireActions")))
                      {
                          v->Add(Model::FAcquireAction::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FAcquireActionPtr>>())
          ->WithVerifyActions(Data->HasField(ANSI_TO_TCHAR("verifyActions")) ? [Data]() -> TSharedPtr<TArray<Model::FVerifyActionPtr>>
              {
                  auto v = MakeShared<TArray<Model::FVerifyActionPtr>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("verifyActions")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("verifyActions")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("verifyActions")))
                      {
                          v->Add(Model::FVerifyAction::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FVerifyActionPtr>>())
          ->WithConsumeActions(Data->HasField(ANSI_TO_TCHAR("consumeActions")) ? [Data]() -> TSharedPtr<TArray<Model::FConsumeActionPtr>>
              {
                  auto v = MakeShared<TArray<Model::FConsumeActionPtr>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("consumeActions")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("consumeActions")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("consumeActions")))
                      {
                          v->Add(Model::FConsumeAction::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FConsumeActionPtr>>());
    }

    TSharedPtr<FJsonObject> FUpdateRateModelMasterRequest::ToJson() const
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
        if (TimingTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("timingType", TimingTypeValue.GetValue());
        }
        if (LockTimeValue.IsSet())
        {
            JsonRootObject->SetNumberField("lockTime", LockTimeValue.GetValue());
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
        if (VerifyActionsValue != nullptr && VerifyActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *VerifyActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("verifyActions", v);
        }
        if (ConsumeActionsValue != nullptr && ConsumeActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ConsumeActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("consumeActions", v);
        }
        return JsonRootObject;
    }
}