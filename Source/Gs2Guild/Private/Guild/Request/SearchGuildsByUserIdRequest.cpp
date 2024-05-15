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

#include "Guild/Request/SearchGuildsByUserIdRequest.h"

namespace Gs2::Guild::Request
{
    FSearchGuildsByUserIdRequest::FSearchGuildsByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        GuildModelNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        DisplayNameValue(TOptional<FString>()),
        Attributes1Value(nullptr),
        Attributes2Value(nullptr),
        Attributes3Value(nullptr),
        Attributes4Value(nullptr),
        Attributes5Value(nullptr),
        JoinPoliciesValue(nullptr),
        IncludeFullMembersGuildValue(TOptional<bool>()),
        PageTokenValue(TOptional<FString>()),
        LimitValue(TOptional<int32>()),
        TimeOffsetTokenValue(TOptional<FString>())
    {
    }

    FSearchGuildsByUserIdRequest::FSearchGuildsByUserIdRequest(
        const FSearchGuildsByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        GuildModelNameValue(From.GuildModelNameValue),
        UserIdValue(From.UserIdValue),
        DisplayNameValue(From.DisplayNameValue),
        Attributes1Value(From.Attributes1Value),
        Attributes2Value(From.Attributes2Value),
        Attributes3Value(From.Attributes3Value),
        Attributes4Value(From.Attributes4Value),
        Attributes5Value(From.Attributes5Value),
        JoinPoliciesValue(From.JoinPoliciesValue),
        IncludeFullMembersGuildValue(From.IncludeFullMembersGuildValue),
        PageTokenValue(From.PageTokenValue),
        LimitValue(From.LimitValue),
        TimeOffsetTokenValue(From.TimeOffsetTokenValue)
    {
    }

    TSharedPtr<FSearchGuildsByUserIdRequest> FSearchGuildsByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FSearchGuildsByUserIdRequest> FSearchGuildsByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FSearchGuildsByUserIdRequest> FSearchGuildsByUserIdRequest::WithGuildModelName(
        const TOptional<FString> GuildModelName
    )
    {
        this->GuildModelNameValue = GuildModelName;
        return SharedThis(this);
    }

    TSharedPtr<FSearchGuildsByUserIdRequest> FSearchGuildsByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FSearchGuildsByUserIdRequest> FSearchGuildsByUserIdRequest::WithDisplayName(
        const TOptional<FString> DisplayName
    )
    {
        this->DisplayNameValue = DisplayName;
        return SharedThis(this);
    }

    TSharedPtr<FSearchGuildsByUserIdRequest> FSearchGuildsByUserIdRequest::WithAttributes1(
        const TSharedPtr<TArray<int32>> Attributes1
    )
    {
        this->Attributes1Value = Attributes1;
        return SharedThis(this);
    }

    TSharedPtr<FSearchGuildsByUserIdRequest> FSearchGuildsByUserIdRequest::WithAttributes2(
        const TSharedPtr<TArray<int32>> Attributes2
    )
    {
        this->Attributes2Value = Attributes2;
        return SharedThis(this);
    }

    TSharedPtr<FSearchGuildsByUserIdRequest> FSearchGuildsByUserIdRequest::WithAttributes3(
        const TSharedPtr<TArray<int32>> Attributes3
    )
    {
        this->Attributes3Value = Attributes3;
        return SharedThis(this);
    }

    TSharedPtr<FSearchGuildsByUserIdRequest> FSearchGuildsByUserIdRequest::WithAttributes4(
        const TSharedPtr<TArray<int32>> Attributes4
    )
    {
        this->Attributes4Value = Attributes4;
        return SharedThis(this);
    }

    TSharedPtr<FSearchGuildsByUserIdRequest> FSearchGuildsByUserIdRequest::WithAttributes5(
        const TSharedPtr<TArray<int32>> Attributes5
    )
    {
        this->Attributes5Value = Attributes5;
        return SharedThis(this);
    }

    TSharedPtr<FSearchGuildsByUserIdRequest> FSearchGuildsByUserIdRequest::WithJoinPolicies(
        const TSharedPtr<TArray<FString>> JoinPolicies
    )
    {
        this->JoinPoliciesValue = JoinPolicies;
        return SharedThis(this);
    }

    TSharedPtr<FSearchGuildsByUserIdRequest> FSearchGuildsByUserIdRequest::WithIncludeFullMembersGuild(
        const TOptional<bool> IncludeFullMembersGuild
    )
    {
        this->IncludeFullMembersGuildValue = IncludeFullMembersGuild;
        return SharedThis(this);
    }

    TSharedPtr<FSearchGuildsByUserIdRequest> FSearchGuildsByUserIdRequest::WithPageToken(
        const TOptional<FString> PageToken
    )
    {
        this->PageTokenValue = PageToken;
        return SharedThis(this);
    }

    TSharedPtr<FSearchGuildsByUserIdRequest> FSearchGuildsByUserIdRequest::WithLimit(
        const TOptional<int32> Limit
    )
    {
        this->LimitValue = Limit;
        return SharedThis(this);
    }

    TSharedPtr<FSearchGuildsByUserIdRequest> FSearchGuildsByUserIdRequest::WithTimeOffsetToken(
        const TOptional<FString> TimeOffsetToken
    )
    {
        this->TimeOffsetTokenValue = TimeOffsetToken;
        return SharedThis(this);
    }

    TSharedPtr<FSearchGuildsByUserIdRequest> FSearchGuildsByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FSearchGuildsByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FSearchGuildsByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FSearchGuildsByUserIdRequest::GetGuildModelName() const
    {
        return GuildModelNameValue;
    }

    TOptional<FString> FSearchGuildsByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FSearchGuildsByUserIdRequest::GetDisplayName() const
    {
        return DisplayNameValue;
    }

    TSharedPtr<TArray<int32>> FSearchGuildsByUserIdRequest::GetAttributes1() const
    {
        if (!Attributes1Value.IsValid())
        {
            return nullptr;
        }
        return Attributes1Value;
    }

    TSharedPtr<TArray<int32>> FSearchGuildsByUserIdRequest::GetAttributes2() const
    {
        if (!Attributes2Value.IsValid())
        {
            return nullptr;
        }
        return Attributes2Value;
    }

    TSharedPtr<TArray<int32>> FSearchGuildsByUserIdRequest::GetAttributes3() const
    {
        if (!Attributes3Value.IsValid())
        {
            return nullptr;
        }
        return Attributes3Value;
    }

    TSharedPtr<TArray<int32>> FSearchGuildsByUserIdRequest::GetAttributes4() const
    {
        if (!Attributes4Value.IsValid())
        {
            return nullptr;
        }
        return Attributes4Value;
    }

    TSharedPtr<TArray<int32>> FSearchGuildsByUserIdRequest::GetAttributes5() const
    {
        if (!Attributes5Value.IsValid())
        {
            return nullptr;
        }
        return Attributes5Value;
    }

    TSharedPtr<TArray<FString>> FSearchGuildsByUserIdRequest::GetJoinPolicies() const
    {
        if (!JoinPoliciesValue.IsValid())
        {
            return nullptr;
        }
        return JoinPoliciesValue;
    }

    TOptional<bool> FSearchGuildsByUserIdRequest::GetIncludeFullMembersGuild() const
    {
        return IncludeFullMembersGuildValue;
    }

    FString FSearchGuildsByUserIdRequest::GetIncludeFullMembersGuildString() const
    {
        if (!IncludeFullMembersGuildValue.IsSet())
        {
            return FString("null");
        }
        return FString(IncludeFullMembersGuildValue.GetValue() ? "true" : "false");
    }

    TOptional<FString> FSearchGuildsByUserIdRequest::GetPageToken() const
    {
        return PageTokenValue;
    }

    TOptional<int32> FSearchGuildsByUserIdRequest::GetLimit() const
    {
        return LimitValue;
    }

    FString FSearchGuildsByUserIdRequest::GetLimitString() const
    {
        if (!LimitValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), LimitValue.GetValue());
    }

    TOptional<FString> FSearchGuildsByUserIdRequest::GetTimeOffsetToken() const
    {
        return TimeOffsetTokenValue;
    }

    TOptional<FString> FSearchGuildsByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FSearchGuildsByUserIdRequest> FSearchGuildsByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSearchGuildsByUserIdRequest>()
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
            ->WithGuildModelName(Data->HasField("guildModelName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("guildModelName", v))
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
            ->WithDisplayName(Data->HasField("displayName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("displayName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithAttributes1(Data->HasField("attributes1") ? [Data]() -> TSharedPtr<TArray<int32>>
              {
                  auto v = MakeShared<TArray<int32>>();
                  if (!Data->HasTypedField<EJson::Null>("attributes1") && Data->HasTypedField<EJson::Array>("attributes1"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("attributes1"))
                      {
                          v->Add(JsonObjectValue->AsNumber());
                      }
                  }
                  return v;
              }() : MakeShared<TArray<int32>>())
          ->WithAttributes2(Data->HasField("attributes2") ? [Data]() -> TSharedPtr<TArray<int32>>
              {
                  auto v = MakeShared<TArray<int32>>();
                  if (!Data->HasTypedField<EJson::Null>("attributes2") && Data->HasTypedField<EJson::Array>("attributes2"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("attributes2"))
                      {
                          v->Add(JsonObjectValue->AsNumber());
                      }
                  }
                  return v;
              }() : MakeShared<TArray<int32>>())
          ->WithAttributes3(Data->HasField("attributes3") ? [Data]() -> TSharedPtr<TArray<int32>>
              {
                  auto v = MakeShared<TArray<int32>>();
                  if (!Data->HasTypedField<EJson::Null>("attributes3") && Data->HasTypedField<EJson::Array>("attributes3"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("attributes3"))
                      {
                          v->Add(JsonObjectValue->AsNumber());
                      }
                  }
                  return v;
              }() : MakeShared<TArray<int32>>())
          ->WithAttributes4(Data->HasField("attributes4") ? [Data]() -> TSharedPtr<TArray<int32>>
              {
                  auto v = MakeShared<TArray<int32>>();
                  if (!Data->HasTypedField<EJson::Null>("attributes4") && Data->HasTypedField<EJson::Array>("attributes4"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("attributes4"))
                      {
                          v->Add(JsonObjectValue->AsNumber());
                      }
                  }
                  return v;
              }() : MakeShared<TArray<int32>>())
          ->WithAttributes5(Data->HasField("attributes5") ? [Data]() -> TSharedPtr<TArray<int32>>
              {
                  auto v = MakeShared<TArray<int32>>();
                  if (!Data->HasTypedField<EJson::Null>("attributes5") && Data->HasTypedField<EJson::Array>("attributes5"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("attributes5"))
                      {
                          v->Add(JsonObjectValue->AsNumber());
                      }
                  }
                  return v;
              }() : MakeShared<TArray<int32>>())
          ->WithJoinPolicies(Data->HasField("joinPolicies") ? [Data]() -> TSharedPtr<TArray<FString>>
              {
                  auto v = MakeShared<TArray<FString>>();
                  if (!Data->HasTypedField<EJson::Null>("joinPolicies") && Data->HasTypedField<EJson::Array>("joinPolicies"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("joinPolicies"))
                      {
                          v->Add(JsonObjectValue->AsString());
                      }
                  }
                  return v;
              }() : MakeShared<TArray<FString>>())
            ->WithIncludeFullMembersGuild(Data->HasField("includeFullMembersGuild") ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField("includeFullMembersGuild", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
            ->WithPageToken(Data->HasField("pageToken") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("pageToken", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithLimit(Data->HasField("limit") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("limit", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithTimeOffsetToken(Data->HasField("timeOffsetToken") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("timeOffsetToken", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FSearchGuildsByUserIdRequest::ToJson() const
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
        if (GuildModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("guildModelName", GuildModelNameValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (DisplayNameValue.IsSet())
        {
            JsonRootObject->SetStringField("displayName", DisplayNameValue.GetValue());
        }
        if (Attributes1Value != nullptr && Attributes1Value.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *Attributes1Value)
            {
                v.Add(MakeShared<FJsonValueNumber>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("attributes1", v);
        }
        if (Attributes2Value != nullptr && Attributes2Value.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *Attributes2Value)
            {
                v.Add(MakeShared<FJsonValueNumber>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("attributes2", v);
        }
        if (Attributes3Value != nullptr && Attributes3Value.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *Attributes3Value)
            {
                v.Add(MakeShared<FJsonValueNumber>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("attributes3", v);
        }
        if (Attributes4Value != nullptr && Attributes4Value.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *Attributes4Value)
            {
                v.Add(MakeShared<FJsonValueNumber>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("attributes4", v);
        }
        if (Attributes5Value != nullptr && Attributes5Value.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *Attributes5Value)
            {
                v.Add(MakeShared<FJsonValueNumber>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("attributes5", v);
        }
        if (JoinPoliciesValue != nullptr && JoinPoliciesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *JoinPoliciesValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("joinPolicies", v);
        }
        if (IncludeFullMembersGuildValue.IsSet())
        {
            JsonRootObject->SetBoolField("includeFullMembersGuild", IncludeFullMembersGuildValue.GetValue());
        }
        if (PageTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("pageToken", PageTokenValue.GetValue());
        }
        if (LimitValue.IsSet())
        {
            JsonRootObject->SetNumberField("limit", LimitValue.GetValue());
        }
        if (TimeOffsetTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("timeOffsetToken", TimeOffsetTokenValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}