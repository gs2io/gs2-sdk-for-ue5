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

#include "Realtime/Model/SyncSetting.h"

namespace Gs2::Realtime::Model
{
    FSyncSetting::FSyncSetting():
        ObjectCatalogValue(TOptional<FString>())
    {
    }

    FSyncSetting::FSyncSetting(
        const FSyncSetting& From
    ):
        ObjectCatalogValue(From.ObjectCatalogValue)
    {
    }

    TSharedPtr<FSyncSetting> FSyncSetting::WithObjectCatalog(
        const TOptional<FString> ObjectCatalog
    )
    {
        this->ObjectCatalogValue = ObjectCatalog;
        return SharedThis(this);
    }
    TOptional<FString> FSyncSetting::GetObjectCatalog() const
    {
        return ObjectCatalogValue;
    }

    TSharedPtr<FSyncSetting> FSyncSetting::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSyncSetting>()
            ->WithObjectCatalog(Data->HasField(ANSI_TO_TCHAR("objectCatalog")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("objectCatalog"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FSyncSetting::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ObjectCatalogValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("objectCatalog"), ObjectCatalogValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FSyncSetting::TypeName = "SyncSetting";
}