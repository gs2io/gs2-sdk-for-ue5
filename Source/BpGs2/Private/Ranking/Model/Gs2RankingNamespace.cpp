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

#include "Ranking/Model/Gs2RankingNamespace.h"
#include "Ranking/Model/Gs2RankingCategoryModel.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Ranking/Model/Gs2RankingCategoryModel.h"
#include "Ranking/Model/Gs2RankingUser.h"
#include "Core/BpGs2Constant.h"

FGs2RankingCategoryModel UGs2RankingNamespaceFunctionLibrary::CategoryModel(
    FGs2RankingNamespace Namespace,
    FString CategoryName
)
{
    FGs2RankingCategoryModel Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingNamespaceFunctionLibrary::CategoryModel] Namespace parameter specification is missing."))
        return Return;
    }
    if (CategoryName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingNamespaceFunctionLibrary::CategoryModel] CategoryName parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->CategoryModel(
        CategoryName
    );
    return Return;
}

FGs2RankingUser UGs2RankingNamespaceFunctionLibrary::User(
    FGs2RankingNamespace Namespace,
    FString UserId
)
{
    FGs2RankingUser Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingNamespaceFunctionLibrary::User] Namespace parameter specification is missing."))
        return Return;
    }
    if (UserId == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingNamespaceFunctionLibrary::User] UserId parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->User(
        UserId
    );
    return Return;
}

FGs2RankingOwnUser UGs2RankingNamespaceFunctionLibrary::Me(
    FGs2RankingNamespace Namespace,
    FGs2AccessToken AccessToken
)
{
    FGs2RankingOwnUser Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingNamespaceFunctionLibrary::Me] Namespace parameter specification is missing."))
        return Return;
    }
    if (AccessToken.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingNamespaceFunctionLibrary::Me] AccessToken parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->Me(AccessToken.Value);
    return Return;
}