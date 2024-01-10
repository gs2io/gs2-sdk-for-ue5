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

#include "Mission/Request/UpdateCounterModelMasterRequest.h"

namespace Gs2::Mission::Request
{
    FUpdateCounterModelMasterRequest::FUpdateCounterModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        CounterNameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        ScopesValue(nullptr),
        ChallengePeriodEventIdValue(TOptional<FString>())
    {
    }

    FUpdateCounterModelMasterRequest::FUpdateCounterModelMasterRequest(
        const FUpdateCounterModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        CounterNameValue(From.CounterNameValue),
        MetadataValue(From.MetadataValue),
        DescriptionValue(From.DescriptionValue),
        ScopesValue(From.ScopesValue),
        ChallengePeriodEventIdValue(From.ChallengePeriodEventIdValue)
    {
    }

    TSharedPtr<FUpdateCounterModelMasterRequest> FUpdateCounterModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCounterModelMasterRequest> FUpdateCounterModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCounterModelMasterRequest> FUpdateCounterModelMasterRequest::WithCounterName(
        const TOptional<FString> CounterName
    )
    {
        this->CounterNameValue = CounterName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCounterModelMasterRequest> FUpdateCounterModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCounterModelMasterRequest> FUpdateCounterModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCounterModelMasterRequest> FUpdateCounterModelMasterRequest::WithScopes(
        const TSharedPtr<TArray<TSharedPtr<Model::FCounterScopeModel>>> Scopes
    )
    {
        this->ScopesValue = Scopes;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCounterModelMasterRequest> FUpdateCounterModelMasterRequest::WithChallengePeriodEventId(
        const TOptional<FString> ChallengePeriodEventId
    )
    {
        this->ChallengePeriodEventIdValue = ChallengePeriodEventId;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateCounterModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateCounterModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateCounterModelMasterRequest::GetCounterName() const
    {
        return CounterNameValue;
    }

    TOptional<FString> FUpdateCounterModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<FString> FUpdateCounterModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FCounterScopeModel>>> FUpdateCounterModelMasterRequest::GetScopes() const
    {
        if (!ScopesValue.IsValid())
        {
            return nullptr;
        }
        return ScopesValue;
    }

    TOptional<FString> FUpdateCounterModelMasterRequest::GetChallengePeriodEventId() const
    {
        return ChallengePeriodEventIdValue;
    }

    TSharedPtr<FUpdateCounterModelMasterRequest> FUpdateCounterModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateCounterModelMasterRequest>()
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
            ->WithCounterName(Data->HasField("counterName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("counterName", v))
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
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("description", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithScopes(Data->HasField("scopes") ? [Data]() -> TSharedPtr<TArray<Model::FCounterScopeModelPtr>>
              {
                  auto v = MakeShared<TArray<Model::FCounterScopeModelPtr>>();
                  if (!Data->HasTypedField<EJson::Null>("scopes") && Data->HasTypedField<EJson::Array>("scopes"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("scopes"))
                      {
                          v->Add(Model::FCounterScopeModel::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FCounterScopeModelPtr>>())
            ->WithChallengePeriodEventId(Data->HasField("challengePeriodEventId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("challengePeriodEventId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FUpdateCounterModelMasterRequest::ToJson() const
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
        if (CounterNameValue.IsSet())
        {
            JsonRootObject->SetStringField("counterName", CounterNameValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (ScopesValue != nullptr && ScopesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ScopesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("scopes", v);
        }
        if (ChallengePeriodEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField("challengePeriodEventId", ChallengePeriodEventIdValue.GetValue());
        }
        return JsonRootObject;
    }
}