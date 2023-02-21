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

#include "Friend/Model/FriendUser.h"

namespace Gs2::Friend::Model
{
    FFriendUser::FFriendUser():
        UserIdValue(TOptional<FString>()),
        PublicProfileValue(TOptional<FString>()),
        FriendProfileValue(TOptional<FString>())
    {
    }

    FFriendUser::FFriendUser(
        const FFriendUser& From
    ):
        UserIdValue(From.UserIdValue),
        PublicProfileValue(From.PublicProfileValue),
        FriendProfileValue(From.FriendProfileValue)
    {
    }

    TSharedPtr<FFriendUser> FFriendUser::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FFriendUser> FFriendUser::WithPublicProfile(
        const TOptional<FString> PublicProfile
    )
    {
        this->PublicProfileValue = PublicProfile;
        return SharedThis(this);
    }

    TSharedPtr<FFriendUser> FFriendUser::WithFriendProfile(
        const TOptional<FString> FriendProfile
    )
    {
        this->FriendProfileValue = FriendProfile;
        return SharedThis(this);
    }
    TOptional<FString> FFriendUser::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FFriendUser::GetPublicProfile() const
    {
        return PublicProfileValue;
    }
    TOptional<FString> FFriendUser::GetFriendProfile() const
    {
        return FriendProfileValue;
    }

    TSharedPtr<FFriendUser> FFriendUser::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FFriendUser>()
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("userId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithPublicProfile(Data->HasField("publicProfile") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("publicProfile", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithFriendProfile(Data->HasField("friendProfile") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("friendProfile", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FFriendUser::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (PublicProfileValue.IsSet())
        {
            JsonRootObject->SetStringField("publicProfile", PublicProfileValue.GetValue());
        }
        if (FriendProfileValue.IsSet())
        {
            JsonRootObject->SetStringField("friendProfile", FriendProfileValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FFriendUser::TypeName = "FriendUser";
}