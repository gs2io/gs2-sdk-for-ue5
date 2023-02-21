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

#include "Lottery/Request/CreatePrizeTableMasterRequest.h"

namespace Gs2::Lottery::Request
{
    FCreatePrizeTableMasterRequest::FCreatePrizeTableMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        PrizesValue(nullptr)
    {
    }

    FCreatePrizeTableMasterRequest::FCreatePrizeTableMasterRequest(
        const FCreatePrizeTableMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        PrizesValue(From.PrizesValue)
    {
    }

    TSharedPtr<FCreatePrizeTableMasterRequest> FCreatePrizeTableMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCreatePrizeTableMasterRequest> FCreatePrizeTableMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FCreatePrizeTableMasterRequest> FCreatePrizeTableMasterRequest::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FCreatePrizeTableMasterRequest> FCreatePrizeTableMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FCreatePrizeTableMasterRequest> FCreatePrizeTableMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FCreatePrizeTableMasterRequest> FCreatePrizeTableMasterRequest::WithPrizes(
        const TSharedPtr<TArray<TSharedPtr<Model::FPrize>>> Prizes
    )
    {
        this->PrizesValue = Prizes;
        return SharedThis(this);
    }

    TOptional<FString> FCreatePrizeTableMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCreatePrizeTableMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FCreatePrizeTableMasterRequest::GetName() const
    {
        return NameValue;
    }

    TOptional<FString> FCreatePrizeTableMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FCreatePrizeTableMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FPrize>>> FCreatePrizeTableMasterRequest::GetPrizes() const
    {
        if (!PrizesValue.IsValid())
        {
            return nullptr;
        }
        return PrizesValue;
    }

    TSharedPtr<FCreatePrizeTableMasterRequest> FCreatePrizeTableMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreatePrizeTableMasterRequest>()
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
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("name", v))
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

    TSharedPtr<FJsonObject> FCreatePrizeTableMasterRequest::ToJson() const
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