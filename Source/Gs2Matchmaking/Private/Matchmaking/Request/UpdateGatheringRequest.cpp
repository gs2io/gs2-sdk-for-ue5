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

#include "Matchmaking/Request/UpdateGatheringRequest.h"

namespace Gs2::Matchmaking::Request
{
    FUpdateGatheringRequest::FUpdateGatheringRequest():
        NamespaceNameValue(TOptional<FString>()),
        GatheringNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        AttributeRangesValue(nullptr)
    {
    }

    FUpdateGatheringRequest::FUpdateGatheringRequest(
        const FUpdateGatheringRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        GatheringNameValue(From.GatheringNameValue),
        AccessTokenValue(From.AccessTokenValue),
        AttributeRangesValue(From.AttributeRangesValue)
    {
    }

    TSharedPtr<FUpdateGatheringRequest> FUpdateGatheringRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGatheringRequest> FUpdateGatheringRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGatheringRequest> FUpdateGatheringRequest::WithGatheringName(
        const TOptional<FString> GatheringName
    )
    {
        this->GatheringNameValue = GatheringName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGatheringRequest> FUpdateGatheringRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGatheringRequest> FUpdateGatheringRequest::WithAttributeRanges(
        const TSharedPtr<TArray<TSharedPtr<Model::FAttributeRange>>> AttributeRanges
    )
    {
        this->AttributeRangesValue = AttributeRanges;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGatheringRequest> FUpdateGatheringRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateGatheringRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateGatheringRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateGatheringRequest::GetGatheringName() const
    {
        return GatheringNameValue;
    }

    TOptional<FString> FUpdateGatheringRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FAttributeRange>>> FUpdateGatheringRequest::GetAttributeRanges() const
    {
        if (!AttributeRangesValue.IsValid())
        {
            return nullptr;
        }
        return AttributeRangesValue;
    }

    TOptional<FString> FUpdateGatheringRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FUpdateGatheringRequest> FUpdateGatheringRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateGatheringRequest>()
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
            ->WithGatheringName(Data->HasField("gatheringName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("gatheringName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithAccessToken(Data->HasField("xGs2AccessToken") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("xGs2AccessToken", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithAttributeRanges(Data->HasField("attributeRanges") ? [Data]() -> TSharedPtr<TArray<Model::FAttributeRangePtr>>
              {
                  auto v = MakeShared<TArray<Model::FAttributeRangePtr>>();
                  if (!Data->HasTypedField<EJson::Null>("attributeRanges") && Data->HasTypedField<EJson::Array>("attributeRanges"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("attributeRanges"))
                      {
                          v->Add(Model::FAttributeRange::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr)
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FUpdateGatheringRequest::ToJson() const
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
        if (GatheringNameValue.IsSet())
        {
            JsonRootObject->SetStringField("gatheringName", GatheringNameValue.GetValue());
        }
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("xGs2AccessToken", AccessTokenValue.GetValue());
        }
        if (AttributeRangesValue != nullptr && AttributeRangesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *AttributeRangesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("attributeRanges", v);
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}