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

#include "Friend/Model/PublicProfile.h"

namespace Gs2::Friend::Model
{
    FPublicProfile::FPublicProfile():
        UserIdValue(TOptional<FString>()),
        PublicProfileValue(TOptional<FString>())
    {
    }

    FPublicProfile::FPublicProfile(
        const FPublicProfile& From
    ):
        UserIdValue(From.UserIdValue),
        PublicProfileValue(From.PublicProfileValue)
    {
    }

    TSharedPtr<FPublicProfile> FPublicProfile::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FPublicProfile> FPublicProfile::WithPublicProfile(
        const TOptional<FString> PublicProfile
    )
    {
        this->PublicProfileValue = PublicProfile;
        return SharedThis(this);
    }
    TOptional<FString> FPublicProfile::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FPublicProfile::GetPublicProfile() const
    {
        return PublicProfileValue;
    }

    TSharedPtr<FPublicProfile> FPublicProfile::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FPublicProfile>()
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
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FPublicProfile::ToJson() const
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
        return JsonRootObject;
    }

    FString FPublicProfile::TypeName = "PublicProfile";
}