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

#pragma once

#include "CoreMinimal.h"
#include "Guild/Domain/Model/UserAccessToken.h"
#include "Guild/Model/Gs2GuildEzJoinedGuild.h"
#include "Util/Net/GameSession.h"

namespace Gs2::UE5::Guild::Domain::Iterator
{

	class EZGS2_API FEzDescribeJoinedGuildsIterator :
        public TSharedFromThis<FEzDescribeJoinedGuildsIterator>
    {
        Gs2::Guild::Domain::Iterator::FDescribeJoinedGuildsIteratorPtr It;
        Gs2::Guild::Domain::Model::FUserAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr Connection;
        TOptional<FString> GuildModelName;

	public:

        explicit FEzDescribeJoinedGuildsIterator(
            Gs2::Guild::Domain::Model::FUserAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection,
            TOptional<FString> GuildModelName = TOptional<FString>()
        ) :
            It(
                Domain->JoinedGuilds(
                    GuildModelName
                )
            ),
            Domain(Domain),
            GameSession(GameSession),
            Connection(Connection),
            GuildModelName(GuildModelName)
        {
        }

		FEzDescribeJoinedGuildsIterator(
			const FEzDescribeJoinedGuildsIterator& From
		) :
			It(From.It),
			Domain(From.Domain),
			GameSession(From.GameSession),
			Connection(From.Connection),
            GuildModelName(From.GuildModelName)
		{
		}

		class EZGS2_API FIterator
		{
		    friend class FEzDescribeJoinedGuildsIterator;

			Gs2::Guild::Domain::Iterator::FDescribeJoinedGuildsIterator::FIterator DomainIterator;
			Gs2::UE5::Guild::Model::FEzJoinedGuildPtr CurrentValue;
        	static Gs2::UE5::Guild::Model::FEzJoinedGuildPtr ConvertCurrent(
        		Gs2::Guild::Domain::Iterator::FDescribeJoinedGuildsIterator::FIterator& DomainIterator
        	)
        	{
				return DomainIterator.IsCurrentValid()
	    			? Gs2::UE5::Guild::Model::FEzJoinedGuild::FromModel(DomainIterator.Current())
					: nullptr;
        	}

			explicit FIterator(
				Gs2::Guild::Domain::Iterator::FDescribeJoinedGuildsIterator::FIterator&& DomainIterator
			) :
			    DomainIterator(DomainIterator),
			    CurrentValue(ConvertCurrent(DomainIterator))
			{}

		public:
			explicit FIterator(
				FEzDescribeJoinedGuildsIterator& Iterable
			) :
			    FIterator(Iterable.begin())
			{}

			FIterator(
			    const FIterator& Iterator
            ) :
                DomainIterator(Iterator.DomainIterator),
                CurrentValue(Iterator.CurrentValue)
            {}

			FIterator& operator*()
			{
				return *this;
			}

			const FIterator& operator*() const
			{
				return *this;
			}

			FIterator* operator->()
			{
				return this;
			}

			const FIterator* operator->() const
			{
				return this;
			}

			FIterator& operator++()
			{
				++DomainIterator;
				CurrentValue = ConvertCurrent(DomainIterator);
				return *this;
			}
            Gs2::UE5::Guild::Model::FEzJoinedGuildPtr& Current()
            {
                return CurrentValue;
            }

            Gs2::Core::Model::FGs2ErrorPtr Error()
            {
                return DomainIterator.Error();
            }

            bool IsError() const
            {
                return DomainIterator.IsError();
            }

            void Retry()
            {
                DomainIterator.Retry();
            }

			friend bool operator== (const FIterator& a, const FIterator& b)
			{
				return a.DomainIterator == b.DomainIterator;
			}
			friend bool operator!= (const FIterator& a, const FIterator& b)
			{
				return !operator==(a, b);
			}
		};

		FIterator OneBeforeBegin()
		{
			return FIterator(It->OneBeforeBegin());
		}
		FIterator begin()
		{
			return FIterator(It->begin());
		}
		FIterator end()
		{
			return FIterator(It->end());
		}
    };
	typedef TSharedPtr<FEzDescribeJoinedGuildsIterator> FEzDescribeJoinedGuildsIteratorPtr;
}
