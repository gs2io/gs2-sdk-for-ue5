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

#include "Account/Model/AccountDeletionSetting.h"

namespace Gs2::Account::Model
{
    FAccountDeletionSetting::FAccountDeletionSetting():
        GracePeriodMinutesValue(TOptional<int32>()),
        LoginDuringGracePeriodValue(TOptional<FString>()),
        CleanUserDataScopeValue(TOptional<FString>())
    {
    }

    FAccountDeletionSetting::FAccountDeletionSetting(
        const FAccountDeletionSetting& From
    ):
        GracePeriodMinutesValue(From.GracePeriodMinutesValue),
        LoginDuringGracePeriodValue(From.LoginDuringGracePeriodValue),
        CleanUserDataScopeValue(From.CleanUserDataScopeValue)
    {
    }

    TSharedPtr<FAccountDeletionSetting> FAccountDeletionSetting::WithGracePeriodMinutes(
        const TOptional<int32> GracePeriodMinutes
    )
    {
        this->GracePeriodMinutesValue = GracePeriodMinutes;
        return SharedThis(this);
    }

    TSharedPtr<FAccountDeletionSetting> FAccountDeletionSetting::WithLoginDuringGracePeriod(
        const TOptional<FString> LoginDuringGracePeriod
    )
    {
        this->LoginDuringGracePeriodValue = LoginDuringGracePeriod;
        return SharedThis(this);
    }

    TSharedPtr<FAccountDeletionSetting> FAccountDeletionSetting::WithCleanUserDataScope(
        const TOptional<FString> CleanUserDataScope
    )
    {
        this->CleanUserDataScopeValue = CleanUserDataScope;
        return SharedThis(this);
    }
    TOptional<int32> FAccountDeletionSetting::GetGracePeriodMinutes() const
    {
        return GracePeriodMinutesValue;
    }

    FString FAccountDeletionSetting::GetGracePeriodMinutesString() const
    {
        if (!GracePeriodMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), GracePeriodMinutesValue.GetValue());
    }
    TOptional<FString> FAccountDeletionSetting::GetLoginDuringGracePeriod() const
    {
        return LoginDuringGracePeriodValue;
    }
    TOptional<FString> FAccountDeletionSetting::GetCleanUserDataScope() const
    {
        return CleanUserDataScopeValue;
    }

    TSharedPtr<FAccountDeletionSetting> FAccountDeletionSetting::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAccountDeletionSetting>()
            ->WithGracePeriodMinutes(Data->HasField(ANSI_TO_TCHAR("gracePeriodMinutes")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("gracePeriodMinutes"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithLoginDuringGracePeriod(Data->HasField(ANSI_TO_TCHAR("loginDuringGracePeriod")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("loginDuringGracePeriod"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCleanUserDataScope(Data->HasField(ANSI_TO_TCHAR("cleanUserDataScope")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("cleanUserDataScope"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FAccountDeletionSetting::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (GracePeriodMinutesValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("gracePeriodMinutes"), GracePeriodMinutesValue.GetValue());
        }
        if (LoginDuringGracePeriodValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("loginDuringGracePeriod"), LoginDuringGracePeriodValue.GetValue());
        }
        if (CleanUserDataScopeValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("cleanUserDataScope"), CleanUserDataScopeValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FAccountDeletionSetting::TypeName = "AccountDeletionSetting";
}