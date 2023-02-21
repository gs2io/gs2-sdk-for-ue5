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

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Auth/Gs2Auth.h"
#include "Key/Gs2Key.h"
#include "Key/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Key/Domain/Iterator/DescribeKeysIterator.h"
#include "Key/Domain/Iterator/DescribeGitHubApiKeysIterator.h"

namespace Gs2::Key::Domain::Model
{
    class FNamespaceDomain;
    class FKeyDomain;
    class FGitHubApiKeyDomain;

    class GS2KEY_API FKeyDomain:
        public TSharedFromThis<FKeyDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Key::FGs2KeyRestClientPtr Client;

        public:
        TOptional<FString> Data;
        TOptional<FString> GetData() const
        {
            return Data;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> KeyName;
    private:

        FString ParentKey;

    public:

        FKeyDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> KeyName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FKeyDomain(
            const FKeyDomain& From
        );

        class GS2KEY_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Key::Domain::Model::FKeyDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FKeyDomain> Self;
            const Request::FUpdateKeyRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FKeyDomain> Self,
                const Request::FUpdateKeyRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Key::Domain::Model::FKeyDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateKeyRequestPtr Request
        );

        class GS2KEY_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Key::Model::FKey>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FKeyDomain> Self;
            const Request::FGetKeyRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FKeyDomain> Self,
                const Request::FGetKeyRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Key::Model::FKey>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetKeyRequestPtr Request
        );

        class GS2KEY_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Key::Domain::Model::FKeyDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FKeyDomain> Self;
            const Request::FDeleteKeyRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FKeyDomain> Self,
                const Request::FDeleteKeyRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Key::Domain::Model::FKeyDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteKeyRequestPtr Request
        );

        class GS2KEY_API FEncryptTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Key::Domain::Model::FKeyDomain>,
            public TSharedFromThis<FEncryptTask>
        {
            const TSharedPtr<FKeyDomain> Self;
            const Request::FEncryptRequestPtr Request;
        public:
            explicit FEncryptTask(
                const TSharedPtr<FKeyDomain> Self,
                const Request::FEncryptRequestPtr Request
            );

            FEncryptTask(
                const FEncryptTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Key::Domain::Model::FKeyDomain>> Result
            ) override;
        };
        friend FEncryptTask;

        TSharedPtr<FAsyncTask<FEncryptTask>> Encrypt(
            Request::FEncryptRequestPtr Request
        );

        class GS2KEY_API FDecryptTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Key::Domain::Model::FKeyDomain>,
            public TSharedFromThis<FDecryptTask>
        {
            const TSharedPtr<FKeyDomain> Self;
            const Request::FDecryptRequestPtr Request;
        public:
            explicit FDecryptTask(
                const TSharedPtr<FKeyDomain> Self,
                const Request::FDecryptRequestPtr Request
            );

            FDecryptTask(
                const FDecryptTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Key::Domain::Model::FKeyDomain>> Result
            ) override;
        };
        friend FDecryptTask;

        TSharedPtr<FAsyncTask<FDecryptTask>> Decrypt(
            Request::FDecryptRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> KeyName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> KeyName
        );

        class GS2KEY_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Key::Model::FKey>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FKeyDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FKeyDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Key::Model::FKey>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FKeyDomain> FKeyDomainPtr;
}
