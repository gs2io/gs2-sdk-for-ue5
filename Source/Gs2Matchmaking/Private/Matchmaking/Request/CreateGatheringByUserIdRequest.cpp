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

#include "Matchmaking/Request/CreateGatheringByUserIdRequest.h"

namespace Gs2::Matchmaking::Request
{
    FCreateGatheringByUserIdRequest::FCreateGatheringByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        PlayerValue(nullptr),
        AttributeRangesValue(nullptr),
        CapacityOfRolesValue(nullptr),
        AllowUserIdsValue(nullptr),
        ExpiresAtValue(TOptional<int64>()),
        ExpiresAtTimeSpanValue(nullptr)
    {
    }

    FCreateGatheringByUserIdRequest::FCreateGatheringByUserIdRequest(
        const FCreateGatheringByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        PlayerValue(From.PlayerValue),
        AttributeRangesValue(From.AttributeRangesValue),
        CapacityOfRolesValue(From.CapacityOfRolesValue),
        AllowUserIdsValue(From.AllowUserIdsValue),
        ExpiresAtValue(From.ExpiresAtValue),
        ExpiresAtTimeSpanValue(From.ExpiresAtTimeSpanValue)
    {
    }

    TSharedPtr<FCreateGatheringByUserIdRequest> FCreateGatheringByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCreateGatheringByUserIdRequest> FCreateGatheringByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FCreateGatheringByUserIdRequest> FCreateGatheringByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FCreateGatheringByUserIdRequest> FCreateGatheringByUserIdRequest::WithPlayer(
        const TSharedPtr<Model::FPlayer> Player
    )
    {
        this->PlayerValue = Player;
        return SharedThis(this);
    }

    TSharedPtr<FCreateGatheringByUserIdRequest> FCreateGatheringByUserIdRequest::WithAttributeRanges(
        const TSharedPtr<TArray<TSharedPtr<Model::FAttributeRange>>> AttributeRanges
    )
    {
        this->AttributeRangesValue = AttributeRanges;
        return SharedThis(this);
    }

    TSharedPtr<FCreateGatheringByUserIdRequest> FCreateGatheringByUserIdRequest::WithCapacityOfRoles(
        const TSharedPtr<TArray<TSharedPtr<Model::FCapacityOfRole>>> CapacityOfRoles
    )
    {
        this->CapacityOfRolesValue = CapacityOfRoles;
        return SharedThis(this);
    }

    TSharedPtr<FCreateGatheringByUserIdRequest> FCreateGatheringByUserIdRequest::WithAllowUserIds(
        const TSharedPtr<TArray<FString>> AllowUserIds
    )
    {
        this->AllowUserIdsValue = AllowUserIds;
        return SharedThis(this);
    }

    TSharedPtr<FCreateGatheringByUserIdRequest> FCreateGatheringByUserIdRequest::WithExpiresAt(
        const TOptional<int64> ExpiresAt
    )
    {
        this->ExpiresAtValue = ExpiresAt;
        return SharedThis(this);
    }

    TSharedPtr<FCreateGatheringByUserIdRequest> FCreateGatheringByUserIdRequest::WithExpiresAtTimeSpan(
        const TSharedPtr<Model::FTimeSpan> ExpiresAtTimeSpan
    )
    {
        this->ExpiresAtTimeSpanValue = ExpiresAtTimeSpan;
        return SharedThis(this);
    }

    TSharedPtr<FCreateGatheringByUserIdRequest> FCreateGatheringByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FCreateGatheringByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCreateGatheringByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FCreateGatheringByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TSharedPtr<Model::FPlayer> FCreateGatheringByUserIdRequest::GetPlayer() const
    {
        if (!PlayerValue.IsValid())
        {
            return nullptr;
        }
        return PlayerValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FAttributeRange>>> FCreateGatheringByUserIdRequest::GetAttributeRanges() const
    {
        if (!AttributeRangesValue.IsValid())
        {
            return nullptr;
        }
        return AttributeRangesValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FCapacityOfRole>>> FCreateGatheringByUserIdRequest::GetCapacityOfRoles() const
    {
        if (!CapacityOfRolesValue.IsValid())
        {
            return nullptr;
        }
        return CapacityOfRolesValue;
    }

    TSharedPtr<TArray<FString>> FCreateGatheringByUserIdRequest::GetAllowUserIds() const
    {
        if (!AllowUserIdsValue.IsValid())
        {
            return nullptr;
        }
        return AllowUserIdsValue;
    }

    TOptional<int64> FCreateGatheringByUserIdRequest::GetExpiresAt() const
    {
        return ExpiresAtValue;
    }

    FString FCreateGatheringByUserIdRequest::GetExpiresAtString() const
    {
        if (!ExpiresAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ExpiresAtValue.GetValue());
    }

    TSharedPtr<Model::FTimeSpan> FCreateGatheringByUserIdRequest::GetExpiresAtTimeSpan() const
    {
        if (!ExpiresAtTimeSpanValue.IsValid())
        {
            return nullptr;
        }
        return ExpiresAtTimeSpanValue;
    }

    TOptional<FString> FCreateGatheringByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FCreateGatheringByUserIdRequest> FCreateGatheringByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateGatheringByUserIdRequest>()
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
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("userId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithPlayer(Data->HasField("player") ? [Data]() -> Model::FPlayerPtr
              {
                  if (Data->HasTypedField<EJson::Null>("player"))
                  {
                      return nullptr;
                  }
                  return Model::FPlayer::FromJson(Data->GetObjectField("player"));
             }() : nullptr)
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
          ->WithCapacityOfRoles(Data->HasField("capacityOfRoles") ? [Data]() -> TSharedPtr<TArray<Model::FCapacityOfRolePtr>>
              {
                  auto v = MakeShared<TArray<Model::FCapacityOfRolePtr>>();
                  if (!Data->HasTypedField<EJson::Null>("capacityOfRoles") && Data->HasTypedField<EJson::Array>("capacityOfRoles"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("capacityOfRoles"))
                      {
                          v->Add(Model::FCapacityOfRole::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr)
          ->WithAllowUserIds(Data->HasField("allowUserIds") ? [Data]() -> TSharedPtr<TArray<FString>>
              {
                  auto v = MakeShared<TArray<FString>>();
                  if (!Data->HasTypedField<EJson::Null>("allowUserIds") && Data->HasTypedField<EJson::Array>("allowUserIds"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("allowUserIds"))
                      {
                          v->Add(JsonObjectValue->AsString());
                      }
                  }
                  return v;
             }() : nullptr)
            ->WithExpiresAt(Data->HasField("expiresAt") ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField("expiresAt", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
          ->WithExpiresAtTimeSpan(Data->HasField("expiresAtTimeSpan") ? [Data]() -> Model::FTimeSpanPtr
              {
                  if (Data->HasTypedField<EJson::Null>("expiresAtTimeSpan"))
                  {
                      return nullptr;
                  }
                  return Model::FTimeSpan::FromJson(Data->GetObjectField("expiresAtTimeSpan"));
             }() : nullptr)
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FCreateGatheringByUserIdRequest::ToJson() const
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
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (PlayerValue != nullptr && PlayerValue.IsValid())
        {
            JsonRootObject->SetObjectField("player", PlayerValue->ToJson());
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
        if (CapacityOfRolesValue != nullptr && CapacityOfRolesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *CapacityOfRolesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("capacityOfRoles", v);
        }
        if (AllowUserIdsValue != nullptr && AllowUserIdsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *AllowUserIdsValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("allowUserIds", v);
        }
        if (ExpiresAtValue.IsSet())
        {
            JsonRootObject->SetStringField("expiresAt", FString::Printf(TEXT("%lld"), ExpiresAtValue.GetValue()));
        }
        if (ExpiresAtTimeSpanValue != nullptr && ExpiresAtTimeSpanValue.IsValid())
        {
            JsonRootObject->SetObjectField("expiresAtTimeSpan", ExpiresAtTimeSpanValue->ToJson());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}