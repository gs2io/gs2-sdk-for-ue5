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

#include "Guild/Model/Member.h"

namespace Gs2::Guild::Model
{
    FMember::FMember():
        UserIdValue(TOptional<FString>()),
        RoleNameValue(TOptional<FString>()),
        JoinedAtValue(TOptional<int64>())
    {
    }

    FMember::FMember(
        const FMember& From
    ):
        UserIdValue(From.UserIdValue),
        RoleNameValue(From.RoleNameValue),
        JoinedAtValue(From.JoinedAtValue)
    {
    }

    TSharedPtr<FMember> FMember::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FMember> FMember::WithRoleName(
        const TOptional<FString> RoleName
    )
    {
        this->RoleNameValue = RoleName;
        return SharedThis(this);
    }

    TSharedPtr<FMember> FMember::WithJoinedAt(
        const TOptional<int64> JoinedAt
    )
    {
        this->JoinedAtValue = JoinedAt;
        return SharedThis(this);
    }
    TOptional<FString> FMember::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FMember::GetRoleName() const
    {
        return RoleNameValue;
    }
    TOptional<int64> FMember::GetJoinedAt() const
    {
        return JoinedAtValue;
    }

    FString FMember::GetJoinedAtString() const
    {
        if (!JoinedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), JoinedAtValue.GetValue());
    }

    TSharedPtr<FMember> FMember::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FMember>()
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("userId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRoleName(Data->HasField("roleName") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("roleName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithJoinedAt(Data->HasField("joinedAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("joinedAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FMember::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (RoleNameValue.IsSet())
        {
            JsonRootObject->SetStringField("roleName", RoleNameValue.GetValue());
        }
        if (JoinedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("joinedAt", FString::Printf(TEXT("%lld"), JoinedAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FMember::TypeName = "Member";
}