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

#include "Guild/Request/UpdateGuildByGuildNameRequest.h"

namespace Gs2::Guild::Request
{
    FUpdateGuildByGuildNameRequest::FUpdateGuildByGuildNameRequest():
        NamespaceNameValue(TOptional<FString>()),
        GuildNameValue(TOptional<FString>()),
        GuildModelNameValue(TOptional<FString>()),
        DisplayNameValue(TOptional<FString>()),
        Attribute1Value(TOptional<int32>()),
        Attribute2Value(TOptional<int32>()),
        Attribute3Value(TOptional<int32>()),
        Attribute4Value(TOptional<int32>()),
        Attribute5Value(TOptional<int32>()),
        MetadataValue(TOptional<FString>()),
        JoinPolicyValue(TOptional<FString>()),
        CustomRolesValue(nullptr),
        GuildMemberDefaultRoleValue(TOptional<FString>())
    {
    }

    FUpdateGuildByGuildNameRequest::FUpdateGuildByGuildNameRequest(
        const FUpdateGuildByGuildNameRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        GuildNameValue(From.GuildNameValue),
        GuildModelNameValue(From.GuildModelNameValue),
        DisplayNameValue(From.DisplayNameValue),
        Attribute1Value(From.Attribute1Value),
        Attribute2Value(From.Attribute2Value),
        Attribute3Value(From.Attribute3Value),
        Attribute4Value(From.Attribute4Value),
        Attribute5Value(From.Attribute5Value),
        MetadataValue(From.MetadataValue),
        JoinPolicyValue(From.JoinPolicyValue),
        CustomRolesValue(From.CustomRolesValue),
        GuildMemberDefaultRoleValue(From.GuildMemberDefaultRoleValue)
    {
    }

    TSharedPtr<FUpdateGuildByGuildNameRequest> FUpdateGuildByGuildNameRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGuildByGuildNameRequest> FUpdateGuildByGuildNameRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGuildByGuildNameRequest> FUpdateGuildByGuildNameRequest::WithGuildName(
        const TOptional<FString> GuildName
    )
    {
        this->GuildNameValue = GuildName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGuildByGuildNameRequest> FUpdateGuildByGuildNameRequest::WithGuildModelName(
        const TOptional<FString> GuildModelName
    )
    {
        this->GuildModelNameValue = GuildModelName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGuildByGuildNameRequest> FUpdateGuildByGuildNameRequest::WithDisplayName(
        const TOptional<FString> DisplayName
    )
    {
        this->DisplayNameValue = DisplayName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGuildByGuildNameRequest> FUpdateGuildByGuildNameRequest::WithAttribute1(
        const TOptional<int32> Attribute1
    )
    {
        this->Attribute1Value = Attribute1;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGuildByGuildNameRequest> FUpdateGuildByGuildNameRequest::WithAttribute2(
        const TOptional<int32> Attribute2
    )
    {
        this->Attribute2Value = Attribute2;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGuildByGuildNameRequest> FUpdateGuildByGuildNameRequest::WithAttribute3(
        const TOptional<int32> Attribute3
    )
    {
        this->Attribute3Value = Attribute3;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGuildByGuildNameRequest> FUpdateGuildByGuildNameRequest::WithAttribute4(
        const TOptional<int32> Attribute4
    )
    {
        this->Attribute4Value = Attribute4;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGuildByGuildNameRequest> FUpdateGuildByGuildNameRequest::WithAttribute5(
        const TOptional<int32> Attribute5
    )
    {
        this->Attribute5Value = Attribute5;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGuildByGuildNameRequest> FUpdateGuildByGuildNameRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGuildByGuildNameRequest> FUpdateGuildByGuildNameRequest::WithJoinPolicy(
        const TOptional<FString> JoinPolicy
    )
    {
        this->JoinPolicyValue = JoinPolicy;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGuildByGuildNameRequest> FUpdateGuildByGuildNameRequest::WithCustomRoles(
        const TSharedPtr<TArray<TSharedPtr<Model::FRoleModel>>> CustomRoles
    )
    {
        this->CustomRolesValue = CustomRoles;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGuildByGuildNameRequest> FUpdateGuildByGuildNameRequest::WithGuildMemberDefaultRole(
        const TOptional<FString> GuildMemberDefaultRole
    )
    {
        this->GuildMemberDefaultRoleValue = GuildMemberDefaultRole;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGuildByGuildNameRequest> FUpdateGuildByGuildNameRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateGuildByGuildNameRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateGuildByGuildNameRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateGuildByGuildNameRequest::GetGuildName() const
    {
        return GuildNameValue;
    }

    TOptional<FString> FUpdateGuildByGuildNameRequest::GetGuildModelName() const
    {
        return GuildModelNameValue;
    }

    TOptional<FString> FUpdateGuildByGuildNameRequest::GetDisplayName() const
    {
        return DisplayNameValue;
    }

    TOptional<int32> FUpdateGuildByGuildNameRequest::GetAttribute1() const
    {
        return Attribute1Value;
    }

    FString FUpdateGuildByGuildNameRequest::GetAttribute1String() const
    {
        if (!Attribute1Value.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), Attribute1Value.GetValue());
    }

    TOptional<int32> FUpdateGuildByGuildNameRequest::GetAttribute2() const
    {
        return Attribute2Value;
    }

    FString FUpdateGuildByGuildNameRequest::GetAttribute2String() const
    {
        if (!Attribute2Value.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), Attribute2Value.GetValue());
    }

    TOptional<int32> FUpdateGuildByGuildNameRequest::GetAttribute3() const
    {
        return Attribute3Value;
    }

    FString FUpdateGuildByGuildNameRequest::GetAttribute3String() const
    {
        if (!Attribute3Value.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), Attribute3Value.GetValue());
    }

    TOptional<int32> FUpdateGuildByGuildNameRequest::GetAttribute4() const
    {
        return Attribute4Value;
    }

    FString FUpdateGuildByGuildNameRequest::GetAttribute4String() const
    {
        if (!Attribute4Value.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), Attribute4Value.GetValue());
    }

    TOptional<int32> FUpdateGuildByGuildNameRequest::GetAttribute5() const
    {
        return Attribute5Value;
    }

    FString FUpdateGuildByGuildNameRequest::GetAttribute5String() const
    {
        if (!Attribute5Value.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), Attribute5Value.GetValue());
    }

    TOptional<FString> FUpdateGuildByGuildNameRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<FString> FUpdateGuildByGuildNameRequest::GetJoinPolicy() const
    {
        return JoinPolicyValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FRoleModel>>> FUpdateGuildByGuildNameRequest::GetCustomRoles() const
    {
        if (!CustomRolesValue.IsValid())
        {
            return nullptr;
        }
        return CustomRolesValue;
    }

    TOptional<FString> FUpdateGuildByGuildNameRequest::GetGuildMemberDefaultRole() const
    {
        return GuildMemberDefaultRoleValue;
    }

    TOptional<FString> FUpdateGuildByGuildNameRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FUpdateGuildByGuildNameRequest> FUpdateGuildByGuildNameRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateGuildByGuildNameRequest>()
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
            ->WithGuildName(Data->HasField(ANSI_TO_TCHAR("guildName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("guildName"), v))
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
            ->WithDisplayName(Data->HasField(ANSI_TO_TCHAR("displayName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("displayName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithAttribute1(Data->HasField(ANSI_TO_TCHAR("attribute1")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("attribute1"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithAttribute2(Data->HasField(ANSI_TO_TCHAR("attribute2")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("attribute2"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithAttribute3(Data->HasField(ANSI_TO_TCHAR("attribute3")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("attribute3"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithAttribute4(Data->HasField(ANSI_TO_TCHAR("attribute4")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("attribute4"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithAttribute5(Data->HasField(ANSI_TO_TCHAR("attribute5")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("attribute5"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithMetadata(Data->HasField(ANSI_TO_TCHAR("metadata")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("metadata"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithJoinPolicy(Data->HasField(ANSI_TO_TCHAR("joinPolicy")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("joinPolicy"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithCustomRoles(Data->HasField(ANSI_TO_TCHAR("customRoles")) ? [Data]() -> TSharedPtr<TArray<Model::FRoleModelPtr>>
              {
                  auto v = MakeShared<TArray<Model::FRoleModelPtr>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("customRoles")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("customRoles")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("customRoles")))
                      {
                          v->Add(Model::FRoleModel::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FRoleModelPtr>>())
            ->WithGuildMemberDefaultRole(Data->HasField(ANSI_TO_TCHAR("guildMemberDefaultRole")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("guildMemberDefaultRole"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithDuplicationAvoider(Data->HasField(ANSI_TO_TCHAR("duplicationAvoider")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("duplicationAvoider"))) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FUpdateGuildByGuildNameRequest::ToJson() const
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
        if (GuildNameValue.IsSet())
        {
            JsonRootObject->SetStringField("guildName", GuildNameValue.GetValue());
        }
        if (GuildModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("guildModelName", GuildModelNameValue.GetValue());
        }
        if (DisplayNameValue.IsSet())
        {
            JsonRootObject->SetStringField("displayName", DisplayNameValue.GetValue());
        }
        if (Attribute1Value.IsSet())
        {
            JsonRootObject->SetNumberField("attribute1", Attribute1Value.GetValue());
        }
        if (Attribute2Value.IsSet())
        {
            JsonRootObject->SetNumberField("attribute2", Attribute2Value.GetValue());
        }
        if (Attribute3Value.IsSet())
        {
            JsonRootObject->SetNumberField("attribute3", Attribute3Value.GetValue());
        }
        if (Attribute4Value.IsSet())
        {
            JsonRootObject->SetNumberField("attribute4", Attribute4Value.GetValue());
        }
        if (Attribute5Value.IsSet())
        {
            JsonRootObject->SetNumberField("attribute5", Attribute5Value.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (JoinPolicyValue.IsSet())
        {
            JsonRootObject->SetStringField("joinPolicy", JoinPolicyValue.GetValue());
        }
        if (CustomRolesValue != nullptr && CustomRolesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *CustomRolesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("customRoles", v);
        }
        if (GuildMemberDefaultRoleValue.IsSet())
        {
            JsonRootObject->SetStringField("guildMemberDefaultRole", GuildMemberDefaultRoleValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}