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

#include "Account/Model/IssuedCodeSetting.h"

namespace Gs2::Account::Model
{
    FIssuedCodeSetting::FIssuedCodeSetting():
        ExpiresDaysValue(TOptional<int32>()),
        MaxFailedAttemptsValue(TOptional<int32>()),
        DeleteOnUseValue(TOptional<bool>())
    {
    }

    FIssuedCodeSetting::FIssuedCodeSetting(
        const FIssuedCodeSetting& From
    ):
        ExpiresDaysValue(From.ExpiresDaysValue),
        MaxFailedAttemptsValue(From.MaxFailedAttemptsValue),
        DeleteOnUseValue(From.DeleteOnUseValue)
    {
    }

    TSharedPtr<FIssuedCodeSetting> FIssuedCodeSetting::WithExpiresDays(
        const TOptional<int32> ExpiresDays
    )
    {
        this->ExpiresDaysValue = ExpiresDays;
        return SharedThis(this);
    }

    TSharedPtr<FIssuedCodeSetting> FIssuedCodeSetting::WithMaxFailedAttempts(
        const TOptional<int32> MaxFailedAttempts
    )
    {
        this->MaxFailedAttemptsValue = MaxFailedAttempts;
        return SharedThis(this);
    }

    TSharedPtr<FIssuedCodeSetting> FIssuedCodeSetting::WithDeleteOnUse(
        const TOptional<bool> DeleteOnUse
    )
    {
        this->DeleteOnUseValue = DeleteOnUse;
        return SharedThis(this);
    }
    TOptional<int32> FIssuedCodeSetting::GetExpiresDays() const
    {
        return ExpiresDaysValue;
    }

    FString FIssuedCodeSetting::GetExpiresDaysString() const
    {
        if (!ExpiresDaysValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ExpiresDaysValue.GetValue());
    }
    TOptional<int32> FIssuedCodeSetting::GetMaxFailedAttempts() const
    {
        return MaxFailedAttemptsValue;
    }

    FString FIssuedCodeSetting::GetMaxFailedAttemptsString() const
    {
        if (!MaxFailedAttemptsValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaxFailedAttemptsValue.GetValue());
    }
    TOptional<bool> FIssuedCodeSetting::GetDeleteOnUse() const
    {
        return DeleteOnUseValue;
    }

    FString FIssuedCodeSetting::GetDeleteOnUseString() const
    {
        if (!DeleteOnUseValue.IsSet())
        {
            return FString("null");
        }
        return FString(DeleteOnUseValue.GetValue() ? "true" : "false");
    }

    TSharedPtr<FIssuedCodeSetting> FIssuedCodeSetting::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FIssuedCodeSetting>()
            ->WithExpiresDays(Data->HasField(ANSI_TO_TCHAR("expiresDays")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("expiresDays"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithMaxFailedAttempts(Data->HasField(ANSI_TO_TCHAR("maxFailedAttempts")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("maxFailedAttempts"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithDeleteOnUse(Data->HasField(ANSI_TO_TCHAR("deleteOnUse")) ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("deleteOnUse"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>());
    }

    TSharedPtr<FJsonObject> FIssuedCodeSetting::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ExpiresDaysValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("expiresDays"), ExpiresDaysValue.GetValue());
        }
        if (MaxFailedAttemptsValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("maxFailedAttempts"), MaxFailedAttemptsValue.GetValue());
        }
        if (DeleteOnUseValue.IsSet())
        {
            JsonRootObject->SetBoolField(TEXT("deleteOnUse"), DeleteOnUseValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FIssuedCodeSetting::TypeName = "IssuedCodeSetting";
}