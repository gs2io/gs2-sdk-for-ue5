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

#include "BpGs2/Public/Dictionary/Model/Gs2DictionaryNamespace.h"
#include "BpGs2/Public/Dictionary/Model/Gs2DictionaryEntryModel.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Dictionary/Model/Gs2DictionaryEntryModel.h"
#include "Dictionary/Model/Gs2DictionaryUser.h"
#include "Core/BpGs2Constant.h"

FGs2DictionaryEntryModel UGs2DictionaryNamespaceFunctionLibrary::EntryModel(
    FGs2DictionaryNamespace Namespace,
    FString EntryName
)
{
    FGs2DictionaryEntryModel Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DictionaryNamespaceFunctionLibrary::EntryModel] Namespace parameter specification is missing."))
        return Return;
    }
    if (EntryName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DictionaryNamespaceFunctionLibrary::EntryModel] EntryName parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->EntryModel(
        EntryName
    );
    return Return;
}

FGs2DictionaryOwnUser UGs2DictionaryNamespaceFunctionLibrary::Me(
    FGs2DictionaryNamespace Namespace,
    FGs2AccessToken AccessToken
)
{
    FGs2DictionaryOwnUser Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DictionaryNamespaceFunctionLibrary::Me] Namespace parameter specification is missing."))
        return Return;
    }
    if (AccessToken.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DictionaryNamespaceFunctionLibrary::Me] AccessToken parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->Me(AccessToken.Value);
    return Return;
}