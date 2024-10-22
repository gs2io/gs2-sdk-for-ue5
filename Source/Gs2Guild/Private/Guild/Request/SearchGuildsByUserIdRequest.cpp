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
        OrderByValue(TOptional<FString>()),
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
        OrderByValue(From.OrderByValue),
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

    TSharedPtr<FSearchGuildsByUserIdRequest> FSearchGuildsByUserIdRequest::WithOrderBy(
        const TOptional<FString> OrderBy
    )
    {
        this->OrderByValue = OrderBy;
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

    TOptional<FString> FSearchGuildsByUserIdRequest::GetOrderBy() const
    {
        return OrderByValue;
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
            ->WithGuildModelName(Data->HasField(ANSI_TO_TCHAR("guildModelName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("guildModelName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDisplayName(Data->HasField(ANSI_TO_TCHAR("displayName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("displayName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithAttributes1(Data->HasField(ANSI_TO_TCHAR("attributes1")) ? [Data]() -> TSharedPtr<TArray<int32>>
              {
                  auto v = MakeShared<TArray<int32>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("attributes1")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("attributes1")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("attributes1")))
                      {
                          v->Add(JsonObjectValue->AsNumber());
                      }
                  }
                  return v;
              }() : MakeShared<TArray<int32>>())
          ->WithAttributes2(Data->HasField(ANSI_TO_TCHAR("attributes2")) ? [Data]() -> TSharedPtr<TArray<int32>>
              {
                  auto v = MakeShared<TArray<int32>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("attributes2")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("attributes2")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("attributes2")))
                      {
                          v->Add(JsonObjectValue->AsNumber());
                      }
                  }
                  return v;
              }() : MakeShared<TArray<int32>>())
          ->WithAttributes3(Data->HasField(ANSI_TO_TCHAR("attributes3")) ? [Data]() -> TSharedPtr<TArray<int32>>
              {
                  auto v = MakeShared<TArray<int32>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("attributes3")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("attributes3")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("attributes3")))
                      {
                          v->Add(JsonObjectValue->AsNumber());
                      }
                  }
                  return v;
              }() : MakeShared<TArray<int32>>())
          ->WithAttributes4(Data->HasField(ANSI_TO_TCHAR("attributes4")) ? [Data]() -> TSharedPtr<TArray<int32>>
              {
                  auto v = MakeShared<TArray<int32>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("attributes4")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("attributes4")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("attributes4")))
                      {
                          v->Add(JsonObjectValue->AsNumber());
                      }
                  }
                  return v;
              }() : MakeShared<TArray<int32>>())
          ->WithAttributes5(Data->HasField(ANSI_TO_TCHAR("attributes5")) ? [Data]() -> TSharedPtr<TArray<int32>>
              {
                  auto v = MakeShared<TArray<int32>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("attributes5")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("attributes5")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("attributes5")))
                      {
                          v->Add(JsonObjectValue->AsNumber());
                      }
                  }
                  return v;
              }() : MakeShared<TArray<int32>>())
          ->WithJoinPolicies(Data->HasField(ANSI_TO_TCHAR("joinPolicies")) ? [Data]() -> TSharedPtr<TArray<FString>>
              {
                  auto v = MakeShared<TArray<FString>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("joinPolicies")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("joinPolicies")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("joinPolicies")))
                      {
                          v->Add(JsonObjectValue->AsString());
                      }
                  }
                  return v;
              }() : MakeShared<TArray<FString>>())
            ->WithIncludeFullMembersGuild(Data->HasField(ANSI_TO_TCHAR("includeFullMembersGuild")) ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("includeFullMembersGuild"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
            ->WithOrderBy(Data->HasField(ANSI_TO_TCHAR("orderBy")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("orderBy"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithPageToken(Data->HasField(ANSI_TO_TCHAR("pageToken")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("pageToken"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithLimit(Data->HasField(ANSI_TO_TCHAR("limit")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("limit"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithTimeOffsetToken(Data->HasField(ANSI_TO_TCHAR("timeOffsetToken")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("timeOffsetToken"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithDuplicationAvoider(Data->HasField(ANSI_TO_TCHAR("duplicationAvoider")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("duplicationAvoider"))) : TOptional<FString>());
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
        if (OrderByValue.IsSet())
        {
            JsonRootObject->SetStringField("orderBy", OrderByValue.GetValue());
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