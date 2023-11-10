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

#include "Lottery/Request/UpdatePrizeTableMasterRequest.h"

namespace Gs2::Lottery::Request
{
    FUpdatePrizeTableMasterRequest::FUpdatePrizeTableMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        PrizeTableNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        PrizesValue(nullptr)
    {
    }

    FUpdatePrizeTableMasterRequest::FUpdatePrizeTableMasterRequest(
        const FUpdatePrizeTableMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        PrizeTableNameValue(From.PrizeTableNameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        PrizesValue(From.PrizesValue)
    {
    }

    TSharedPtr<FUpdatePrizeTableMasterRequest> FUpdatePrizeTableMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdatePrizeTableMasterRequest> FUpdatePrizeTableMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdatePrizeTableMasterRequest> FUpdatePrizeTableMasterRequest::WithPrizeTableName(
        const TOptional<FString> PrizeTableName
    )
    {
        this->PrizeTableNameValue = PrizeTableName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdatePrizeTableMasterRequest> FUpdatePrizeTableMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdatePrizeTableMasterRequest> FUpdatePrizeTableMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdatePrizeTableMasterRequest> FUpdatePrizeTableMasterRequest::WithPrizes(
        const TSharedPtr<TArray<TSharedPtr<Model::FPrize>>> Prizes
    )
    {
        this->PrizesValue = Prizes;
        return SharedThis(this);
    }

    TOptional<FString> FUpdatePrizeTableMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdatePrizeTableMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdatePrizeTableMasterRequest::GetPrizeTableName() const
    {
        return PrizeTableNameValue;
    }

    TOptional<FString> FUpdatePrizeTableMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdatePrizeTableMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FPrize>>> FUpdatePrizeTableMasterRequest::GetPrizes() const
    {
        if (!PrizesValue.IsValid())
        {
            return nullptr;
        }
        return PrizesValue;
    }

    TSharedPtr<FUpdatePrizeTableMasterRequest> FUpdatePrizeTableMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdatePrizeTableMasterRequest>()
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
            ->WithPrizeTableName(Data->HasField("prizeTableName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("prizeTableName", v))
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
          ->WithPrizes(Data->HasField("prizes") ? [Data]() -> TSharedPtr<TArray<Model::FPrizePtr>>
              {
                  auto v = MakeShared<TArray<Model::FPrizePtr>>();
                  if (!Data->HasTypedField<EJson::Null>("prizes") && Data->HasTypedField<EJson::Array>("prizes"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("prizes"))
                      {
                          v->Add(Model::FPrize::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr);
    }

    TSharedPtr<FJsonObject> FUpdatePrizeTableMasterRequest::ToJson() const
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
        if (PrizeTableNameValue.IsSet())
        {
            JsonRootObject->SetStringField("prizeTableName", PrizeTableNameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (PrizesValue != nullptr && PrizesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *PrizesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("prizes", v);
        }
        return JsonRootObject;
    }
}